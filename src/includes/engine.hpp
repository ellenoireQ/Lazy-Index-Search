#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>
#include <optional>
#include <string>

#include <includes/config.hpp>

namespace fs = std::filesystem;

/**
 * Lazy Index Search
 *
 * Main engine for indexing file with multiple threading
 */
namespace engine
{
    std::optional<fs::path> search(const fs::path &directory, const fs::path &file_name, Config &config, std::optional<std::vector<std::string>> exclude_path);
}
#endif // ENGINE_HPP