#include <includes/task.hpp>

void Task::mark(std::string path, TaskQueue tsk)
{
    std::lock_guard<std::mutex> guard(this->mutex_lock);
    this->task[path] = tsk;
}

void Task::spawn()
{
}
