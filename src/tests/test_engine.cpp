#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <includes/engine.hpp>
#include <includes/task.hpp>

TEST_CASE("Engine search returns the matching file", "[engine]")
{
    const auto root = std::filesystem::temp_directory_path() / "lazy-index-search-test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "nested");
    std::ofstream(root / "nested" / "file.cpp");

    const auto result = engine::search(root, "file.cpp", std::nullopt);

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

    const auto result = engine::search(root, "missing.cpp", std::nullopt);

    REQUIRE_FALSE(result.has_value());
    std::filesystem::remove_all(root);
}

TEST_CASE("Engine search returns no result for a missing directory", "[engine]")
{
    const auto missing = std::filesystem::temp_directory_path() / "lazy-index-search-missing";
    std::filesystem::remove_all(missing);

    REQUIRE_FALSE(engine::search(missing, "file.cpp", std::nullopt).has_value());
}

TEST_CASE("Task run completes with multiple workers", "[task]")
{
    const auto root = std::filesystem::temp_directory_path() / "lazy-index-search-task-test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "first");
    std::filesystem::create_directories(root / "second");
    Task task;

    task.run(root, "missing.cpp", std::nullopt, 2);

    std::filesystem::remove_all(root);
}
