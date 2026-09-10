#include <includes/task.hpp>

void Task::mark(std::string path, TaskQueue tsk)
{
    std::lock_guard<std::mutex> guard(this->mutex_lock);
    this->task[path] = tsk;
}

TaskQueue Task::get_status(std::string path)
{
    std::lock_guard<std::mutex> guard(this->mutex_lock);
    if (this->task.find(path) == this->task.end())
    {
        this->task[path] = TaskQueue::Pending;
    }
    return this->task[path];
}

void Task::spawn()
{
}
