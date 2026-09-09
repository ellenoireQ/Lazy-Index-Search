#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>
#include <optional>

namespace fs = std::filesystem;

/**
 * Lazy Index Search
 *
 * Main engine for indexing file with multiple threading
 */
namespace engine
{
    std::optional<fs::path> search(const fs::path &directory, const fs::path &file_name);
    std::vector<fs::path> _sort_path(const fs::path &p);
}
#endif // ENGINE_HPP