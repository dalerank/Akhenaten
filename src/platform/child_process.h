#pragma once

#include <string>
#include <vector>

struct child_process {
    void* handle = nullptr;
    int pid = -1;
};

bool child_process_start(const std::vector<std::string>& argv, child_process& out);
int child_process_wait(child_process& process);
