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

            if (it == end_it || results.size() <= 2)
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
                    block(it);
                    continue;
                }
            }
            LOG(CLR_WHITE, current);
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
    return std::nullopt;
}