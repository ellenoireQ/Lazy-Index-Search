#include <functional>
#include <includes/engine.hpp>
#include <includes/log.hpp>
#include <includes/task.hpp>
#include <system_error>

std::optional<fs::path> engine::search(Task &tsk, const fs::path &directory, const fs::path &file_name, std::optional<std::vector<std::string>> exclude_path)
{
    std::error_code ec;

    if (tsk.should_stop())
        return std::nullopt;

    if (!fs::exists(directory, ec) || !fs::is_directory(directory, ec))
    {
        return std::nullopt;
    }

    std::unordered_set<std::string> exclude_set;
    if (exclude_path.has_value()) {
        for (const auto& ex : exclude_path.value()) {
            exclude_set.insert(ex);
        }
    }

    auto it = fs::recursive_directory_iterator(
        directory, 
        fs::directory_options::skip_permission_denied, 
        ec);
    
    if (ec) {
        return std::nullopt;
    }

    auto end_it = fs::recursive_directory_iterator();

    for (; it != end_it; ++it)
    {
        if (tsk.should_stop())
            return std::nullopt;

        std::error_code entry_ec;
        const auto& current = it->path();

        if (!exclude_set.empty() && exclude_set.count(current.string()) > 0)
        {
            block(it);
            continue;
        }

        bool is_regular = fs::is_regular_file(current, entry_ec);
        
        if (entry_ec)
        {
            entry_ec.clear();
            block(it);
            continue;
        }

        if (is_regular && current.filename() == file_name)
        {
            tsk.request_stop();
            LOG(CLR_RED, current);
            return current;
        }
    }

    return std::nullopt;
}

std::optional<fs::path> engine::search(const fs::path &directory, const fs::path &file_name, std::optional<std::vector<std::string>> exclude_path)
{
    Task task;
    return search(task, directory, file_name, exclude_path);
}