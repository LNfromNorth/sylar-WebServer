#include "sylar/config.h" 
#include "sylar/env.h"
#include "sylar/util.h"
#include "sylar/log.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace sylar {

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

// 查找 Base，还是简单的查找 name，所以和 Lookup 感觉不是很能区分开
ConfigVarBase::ptr Config::LookupBase(const std::string& name) {
    RWMutexType::ReadLock lock(GetMutex());
    auto it = GetDatas().find(name);
    return it == GetDatas().end() ? nullptr : it->second;
}
// 列出所有成员，形成 output 这个结构
// prefix 字首，这里作为可拼接参数的前置出现，进行拼接查询
static void ListAllMember(const std::string& prefix,
            const YAML::Node& node,
            std::list<std::pair<std::string, const YAML::Node>>& output) {
    // 字首判断是否符合要求
    if(prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos) {
        SYLAR_LOG_ERROR(g_logger) << "Config invalid name: " << prefix << " : " << node;
        return;
    }                     
    // 向 output 中加入结构
    output.push_back(std::make_pair(prefix, node));
    // 判断是否是 Map 进行递归解析
    if(node.IsMap()) {
        for(auto it = node.begin(); it != node.end(); ++it) {
            ListAllMember(prefix.empty() ? it->first.Scalar() : prefix + "." + it->first.Scalar(), it->second, output);
        }
    }
}

void Config::LoadFromYaml(const YAML::Node& root) {
    std::list<std::pair<std::string, const YAML::Node>> all_nodes;
    // 调用解析，形成一个 pair 结构
    ListAllMember("", root, all_nodes);
    // 进行解析任务
    for(auto& i : all_nodes) {
        std::string key = i.first;
        if(key.empty()){
            continue;
        }
        // 将 name 转化为小写，并且插叙是否存在
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        ConfigVarBase::ptr var = LookupBase(key);
        // 对参数对象进行内容设定
        if(var) {
            if(i.second.IsScalar()) {
                var->fromString(i.second.Scalar());
            } else {
                std::stringstream ss;
                ss << i.second;
                var->fromString(ss.str());
            }
        }
    }
}

static std::map<std::string, uint64_t> s_file2modifytime;
static sylar::Mutex s_mutex;

void Config::LoadFromConfDir(const std::string& path) {
    std::string absoulte_path = sylar::EnvMgr::GetInstance()->getAbsolutePath(path);
    std::vector<std::string> files;
    FSUtil::ListAllFile(files, absoulte_path, ".yml");

    for(auto& i : files) {
        struct stat st;
        lstat(i.c_str(), &st);
        {
            sylar::Mutex::Lock lock(s_mutex);
            if(s_file2modifytime[i] == (uint64_t)st.st_mtime) {
                continue;
            }
            s_file2modifytime[i] = st.st_mtime;
        }
        try {
            YAML::Node root = YAML::LoadFile(i);
            LoadFromYaml(root);
            SYLAR_LOG_INFO(SYLAR_LOG_NAME("system")) << "LoadConfFile file="
                << i << " success";
        } catch(...) {
            SYLAR_LOG_ERROR(SYLAR_LOG_NAME("system")) << "LoadConfFile file="
                << i << " failed";
        }
    }
}

void Config::Visit(std::function<void(ConfigVarBase::ptr)> cb) {
    RWMutexType::ReadLock lock(GetMutex());
    ConfigVarMap& m = GetDatas();
    for(auto it = m.begin(); it != m.end(); ++it) {
        cb(it->second);
    }
}

}