#ifndef TASK_HPP
#define TASK_HPP

#include <mutex>
#include <string>
#include <unordered_map>

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
    void spawn();
};
#endif // TASK_HPP
