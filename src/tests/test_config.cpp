#include <catch2/catch_test_macros.hpp>
#include <includes/config.hpp>

TEST_CASE("Config stores and returns values", "[config]")
{
    Config cfg;

    cfg.set("testing-config", true);
    REQUIRE(cfg.get("testing-config") == true);
}

TEST_CASE("Config returns false after removing a value", "[config]")
{
    Config cfg;

    cfg.set("testing-config", true);

    cfg.remove("testing-config");
    REQUIRE(cfg.get("testing-config") == false);
}