#include <includes/engine.hpp>
#include <functional>
#include <system_error>
#include <includes/log.hpp>

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

    for (; it != end_it; ++it)
    {
        std::error_code entry_ec;
        const auto current = it->path();

        if (fs::is_regular_file(current, entry_ec) && current.filename() == file_name)
        {
            LOG(CLR_RED, current);
            results.push_back(current);

            if (it == end_it)
            {
                return current;
            }
        }
        else
        {

            std::vector<std::string> nulls;
            for (const auto &ex_path : exclude_path.value_or(nulls))
            {
                if (current == ex_path)
                {
                    it.disable_recursion_pending();
                    continue;
                }
            }
            LOG(CLR_WHITE, current);
        }

        if (entry_ec)
        {
            entry_ec.clear();
            it.disable_recursion_pending();
        }
    }

    /**
     * Iterate results
     */
    for (auto res : results)
    {
        LOG(CLR_RED, res);
    }
    return std::nullopt;
}

std::vector<fs::path> engine::_sort_path(const fs::path &p)
{
    std::vector<fs::path> paths;

    std::function<void(const fs::path &)> walk = [&](const fs::path &current)
    {
        std::error_code ec;
        if (!fs::exists(current, ec) || !fs::is_directory(current, ec))
        {
            return;
        }

        paths.push_back(current);

        for (const auto &entry : fs::directory_iterator(current, fs::directory_options::skip_permission_denied, ec))
        {
            if (ec)
            {
                ec.clear();
                continue;
            }

            std::error_code is_dir_ec;
            if (entry.is_directory(is_dir_ec) && !is_dir_ec)
            {
                walk(entry.path());
            }
            else
            {
                is_dir_ec.clear();
            }
        }
    };

    walk(p);
    std::sort(paths.begin(), paths.end());
    return paths;
}