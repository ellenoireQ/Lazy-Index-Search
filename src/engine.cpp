#include <includes/engine.hpp>
#include <functional>

void engine::search(const fs::path &directory, const fs::path &file_name)
{
    bool found = false;
    if (!fs::exists(directory) || !fs::is_directory(directory))
    {
        std::cout << "Directory not found: " << directory << std::endl;
        return;
    }

    auto it = fs::recursive_directory_iterator(directory, fs::directory_options::skip_permission_denied);
    auto end_it = fs::recursive_directory_iterator();

    for (; it != end_it; ++it)
    {
        if (it->path().filename() == file_name)
        {
            std::cout << it->path() << '\n';
            found = true;
        }
    }

    if (found == false)
    {
        const auto paths = engine::_sort_path(directory);
        for (const auto &path : paths)
        {
            std::cout << path << std::endl;
        }
    }
}

std::vector<fs::path> engine::_sort_path(const fs::path &p)
{
    std::vector<fs::path> paths;

    std::function<void(const fs::path &)> walk = [&](const fs::path &current)
    {
        paths.push_back(current);

        if (!fs::exists(current) || !fs::is_directory(current))
        {
            return;
        }

        for (const auto &entry : fs::directory_iterator(current))
        {
            if (entry.is_directory())
            {
                walk(entry.path());
            }
        }
    };

    walk(p);
    std::sort(paths.begin(), paths.end());
    return paths;
}