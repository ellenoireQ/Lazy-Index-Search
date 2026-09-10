#include <functional>
#include <includes/engine.hpp>
#include <includes/log.hpp>
#include <includes/task.hpp>
#include <system_error>

std::optional<fs::path> engine::search(const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path)
{
    std::vector<fs::path> results;
    std::error_code ec;

    if (!fs::exists(directory, ec) || !fs::is_directory(directory, ec))
    {
        std::cout << "Directory not found: " << directory << std::endl;
        return std::nullopt;
    }

    auto it = fs::recursive_directory_iterator(directory, fs::directory_options::skip_permission_denied, ec);
    auto end_it = fs::recursive_directory_iterator();

    /**
     * @current passes current path
     * @block blocking iterate to the folder
     *
     * Current method using unordered_map, something like
     * <current, TaskQueue::Done> <= identified as done because in this iterate will be processed
     */
    Task tsk;
    for (; it != end_it; ++it)
    {
        std::error_code entry_ec;
        const auto current = it->path();
        
        tsk.process_task(current);

        if (fs::is_regular_file(current, entry_ec) && current.filename() == file_name)
        {
            // LOG(CLR_RED, current);
            results.push_back(current);

            // marked as done
            tsk.mark(current, TaskQueue::Done);
        }
        else
        {

            std::vector<std::string> nulls;
            for (const auto &ex_path : exclude_path.value_or(nulls))
            {
                if (current == ex_path)
                {
                    // marked as done
                    tsk.mark(current, TaskQueue::Done);

                    block(it);
                    continue;
                }
            }
            // LOG(CLR_WHITE, current);
            // marked as done
            tsk.mark(current, TaskQueue::Done);
        }

        if (entry_ec)
        {
            entry_ec.clear();
            block(it);
        }
    }

    /**
     * Iterate results
     */
    for (auto res : results)
    {
        LOG(CLR_RED, res);
    }

    if (!results.empty())
    {
        return results.front();
    }
    return std::nullopt;
}