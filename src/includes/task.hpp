#ifndef TASK_HPP
#define TASK_HPP

#include <filesystem>
#include <includes/config.hpp>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

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
    void run(const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path, std::optional<int> count);
    void mark(std::string path, TaskQueue tsk);
    TaskQueue get_status(std::string path);
    void spawn();
    void process_task(const fs::path &current);
};
#endif // TASK_HPP
