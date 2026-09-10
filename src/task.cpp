#include "includes/engine.hpp"
#include <includes/log.hpp>
#include <includes/task.hpp>

void Task::run(const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path)
{
    /**
     * TODO: Implement this!
     */
    engine::search(directory, file_name, config, exclude_path);
}

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

/**
 * Process task queue for a given path
 * Handle the switch logic for task status
 */
void Task::process_task(const fs::path &current)
{
    switch (get_status(current))
    {
    case TaskQueue::Process:
        // Do something
    case TaskQueue::Pending:
        // Do something
    case TaskQueue::Done:
        LOG(CLR_YELLOW, "Processed: " + current.string());
    }
}
