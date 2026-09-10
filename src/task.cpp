#include "includes/engine.hpp"
#include <includes/log.hpp>
#include <includes/task.hpp>
#include <thread>

void Task::run(const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path, std::optional<int> count)
{
    /**
     * TODO: Implement this!
     */
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
    for (const auto p : path)
    {

        // LOG(CLR_RED, total);

        int task_size = path.size() / count.value_or(1);

        std::vector<std::thread> threads;

        for (int i = 0; i < count.value_or(1); ++i)
        {
            int start = i * task_size;
            int end = start + task_size;

            threads.emplace_back(
                [&, start, end]()
                {
                    for (int j = start; j < end; ++j)
                    {
                        mark(path[j], TaskQueue::Process);

                        engine::search(
                            *this,
                            path[j],
                            file_name,
                            config,
                            exclude_path);
                    }
                });
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
        // mark(p, TaskQueue::Process);
        //  engine::search(*this, p, file_name, config, exclude_path);
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
