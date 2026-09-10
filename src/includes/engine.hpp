#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "includes/task.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <includes/config.hpp>

namespace fs = std::filesystem;

/**
 * Lazy Index Search
 *
 * Main engine for indexing file with multiple threading
 */
namespace engine
{
    std::optional<fs::path> search(Task &tsk, const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path);
    std::optional<fs::path> search(const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path);
    /**
     * Block the current directory iterator to skip recursion into it
     */
    static inline void block(fs::recursive_directory_iterator &it)
    {
        it.disable_recursion_pending();
    }
} // namespace engine
#endif // ENGINE_HPP
