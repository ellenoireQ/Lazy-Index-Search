#ifndef TASK_HPP
#define TASK_HPP

#include <atomic>
#include <filesystem>
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
    std::atomic<bool> stop_requested{false};

public:
    void run(const fs::path &directory, const fs::path &file_name, std::optional<std::vector<std::string>> exclude_path, std::optional<int> count);
    void mark(const std::string& path, TaskQueue tsk);
    TaskQueue get_status(const std::string& path);
    void spawn();
    void process_task(const fs::path &current);
    void reset_stop();
    void request_stop();
    bool should_stop() const;
    
    inline void mark_processed() { /* No-op for optimization */ }
    inline bool is_processing(const std::string&) { return false; }
};
#endif // TASK_HPP
