#include <catch2/catch_test_macros.hpp>
#include <includes/engine.hpp>
#include <filesystem>

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