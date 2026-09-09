#include <catch2/catch_test_macros.hpp>
#include <includes/engine.hpp>
#include <filesystem>
#include <fstream>

TEST_CASE("Engine search returns the matching file", "[engine]")
{
    const auto root = std::filesystem::temp_directory_path() / "lazy-index-search-test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "nested");
    std::ofstream(root / "nested" / "file.cpp");

    const auto result = engine::search(root, "file.cpp");

    if (result.has_value())
    {
        INFO("Path is: " << result.value().string());
    }
    else
    {
        INFO("Path is empty (nullopt)");
    }

    REQUIRE(result.has_value());
    REQUIRE(result.value() == root / "nested" / "file.cpp");

    std::filesystem::remove_all(root);
}

TEST_CASE("Engine search returns no result when the file is missing", "[engine]")
{
    const auto root = std::filesystem::temp_directory_path() / "lazy-index-search-test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root);

    const auto result = engine::search(root, "missing.cpp");

    REQUIRE_FALSE(result.has_value());
    std::filesystem::remove_all(root);
}

TEST_CASE("Engine search returns no result for a missing directory", "[engine]")
{
    const auto missing = std::filesystem::temp_directory_path() / "lazy-index-search-missing";
    std::filesystem::remove_all(missing);

    REQUIRE_FALSE(engine::search(missing, "file.cpp").has_value());
}

TEST_CASE("Engine sorts nested directories", "[engine]")
{
    const auto root = std::filesystem::temp_directory_path() / "lazy-index-search-test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "nested");

    const auto paths = engine::_sort_path(root);

    REQUIRE(paths.size() == 2);
    REQUIRE(paths[0] == root);
    REQUIRE(paths[1] == root / "nested");

    std::filesystem::remove_all(root);
}

TEST_CASE("Engine returns no paths for a missing directory", "[engine]")
{
    const auto missing = std::filesystem::temp_directory_path() / "lazy-index-search-missing";
    std::filesystem::remove_all(missing);

    REQUIRE(engine::_sort_path(missing).empty());
}