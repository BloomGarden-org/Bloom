#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int garden_set_repo_path(const char* path);

int garden_init(const char* test_path);

int garden_commit(const char* test_path, const char* msg);

int garden_plant(const char* branch_name);

int garden_checkout(const char* branch_name);

int garden_index_ls();

#ifdef __cplusplus
}
#endif
