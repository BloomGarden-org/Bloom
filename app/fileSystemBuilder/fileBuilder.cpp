#include "fileBuilder.h"
#include <iostream>

#define LOGGER_STATUS LOGGER_ACTIVE
#include "../debugging.h"

#ifndef LOG_PATH
#define LOG_PATH(p) LOG((std::filesystem::absolute(p)).string().c_str())
#endif
#define TESTINGPATH "app\\testing\0"


using SP = staticpath::_staticPath;
using namespace std;


void FileBuilder::build(const std::string& treeHash) {
    nav.walk(treeHash, [&](FOS_metadata* meta, std::string fullPath) {

        LOG("in fileBuilderCallBack");
        fs::path src = SP::_TESTPATH();
        fs::path dest = (src / fullPath).lexically_normal();
    
        if (meta->getType() == "[FOLDER]") {
            fs::create_directories(dest);
        } 
        else if (meta->getType() == "[FILE]"){
            LOG(("\t"+meta->getName()).c_str());
            fs::path filePath = SP::_SEEDROOT(meta->getHash());
    
            fs::create_directories(dest.parent_path());
            if (fs::exists(filePath)) {
    
                fs::copy(filePath, dest, fs::copy_options::overwrite_existing);
            } else {
                cerr << "Missing file in garden store: " << filePath << "\n";
            }
        }
    });  
}

void FileBuilder::reset(){
    for (const auto& entry : fs::directory_iterator(TESTINGPATH)) {
        if (entry.path().filename() == ".garden") {
            continue;
        }
        std::error_code ec; 
        fs::remove_all(entry.path(), ec);

        if (ec) {
            printf("Failed to delete: %s, error: %s\n", entry.path().string().c_str(), ec.message().c_str());
        } else {
            printf("Deleted: %s\n", entry.path().string().c_str());
        }
    }
}
