#include "includes/engine.hpp"
#include <includes/log.hpp>
#include <includes/task.hpp>
#include <thread>

void Task::run(const fs::path &directory, const fs::path &file_name, std::optional<std::vector<std::string>> exclude_path, std::optional<int> count)
{
    /**
     * TODO: Implement this!
     */
    reset_stop();
    std::vector<fs::path> path;
    auto it = fs::directory_iterator(directory);

    std::vector<std::string> nulls;
    for (const auto &n : it)
    {
        bool excluded = false;

        for (const auto &ex_path : exclude_path.value_or(nulls))
        {
            if (n.path() == ex_path)
            {
                excluded = true;
                break;
            }
        }

        if (excluded)
            continue;

        path.push_back(n.path());
    }
    const int worker_count = std::max(1, std::min(count.value_or(1), static_cast<int>(path.size())));
    const int task_size = (static_cast<int>(path.size()) + worker_count - 1) / worker_count;
    std::vector<std::thread> threads;

    for (int i = 0; i < worker_count; ++i)
    {
        const int start = i * task_size;
        const int end = std::min(start + task_size, static_cast<int>(path.size()));

        threads.emplace_back(
            [&, start, end]()
            {
                for (int j = start; j < end; ++j)
                {
                    if (should_stop())
                        break;

                    mark(path[j], TaskQueue::Process);

                    engine::search(
                        *this,
                        path[j],
                        file_name,
                        exclude_path);
                }
            });
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
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

void Task::reset_stop()
{
    stop_requested.store(false);
}

void Task::request_stop()
{
    stop_requested.store(true);
}

bool Task::should_stop() const
{
    return stop_requested.load();
}
