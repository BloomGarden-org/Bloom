#include "Garden_c_api.h"
#include "fileSystemManagement/seed/HashTree.h"
#include "fileSystemWriter/FileWriter.h"
#include "fileSystemBuilder/fileBuilder.h"
#include "paths/GardenPath.h"
#include "fileSystemManagement/index/Index.h"
#include "fileSystemManagement/utilz/GardenProtocol/GardenProtocol.h"
#include "fileSystemManagement/utilz/PathManagement/StaticPath.h"
#include <stdexcept>
#include <iostream>

using SP = staticpath::_staticPath;

extern "C" {

int garden_set_repo_path(const char* path) {
    if (!path) return -1;
    try {
        SP::SET(std::make_unique<GardenPath>(path));
        return 0;
    } catch (...) {
        return -1;
    }
}

int garden_init(const char* test_path) {
    if (!test_path) return -1;
    try {
        Index index;
        HashTree hashT(new FolderNode(test_path));
        fileWriter fw;
        fw.init(&hashT, "INIT", &index);
        index.save();
        return 0;
    } catch (...) {
        return -1;
    }
}

int garden_commit(const char* test_path, const char* msg) {
    if (!test_path || !msg) return -1;
    try {
        Index index;
        index.read();
        HashTree hashT(new FolderNode(test_path));
        fileWriter fw;
        fw.commit(&hashT, msg, &index);
        index.save();
        return 0;
    } catch (...) {
        return -1;
    }
}

int garden_plant(const char* branch_name) {
    if (!branch_name) return -1;
    try {
        Index index;
        index.read();
        index.plant(branch_name);
        index.save();
        return 0;
    } catch (...) {
        return -1;
    }
}

int garden_checkout(const char* branch_name) {
    if (!branch_name) return -1;
    try {
        Index index;
        index.read();
        index.setCurrent(branch_name);

        FileBuilder fb;
        fb.reset();

        GardenTag tag(index.getTagHash());
        fb.build(tag.getRootHash());

        index.save();
        return 0;
    } catch (...) {
        return -1;
    }
}

int garden_index_ls() {
    try {
        Index index;
        index.read();
        index.ls();
        return 0;
    } catch (...) {
        return -1;
    }
}

}
