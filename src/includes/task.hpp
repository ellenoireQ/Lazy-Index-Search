#ifndef TASK_HPP
#define TASK_HPP

#include <filesystem>
#include <mutex>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

enum TaskQueue
{
    Process,
    Pending,
    Done
};

class Task
{
private:
    std::mutex mutex_lock;
    std::unordered_map<std::string, TaskQueue> task;

public:
    void mark(std::string path, TaskQueue tsk);
    TaskQueue get_status(std::string path);
    void spawn();
    void process_task(const fs::path &current);
};
#endif // TASK_HPP
