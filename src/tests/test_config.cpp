#include <includes/config.hpp>
#include <cassert>

int main()
{
    Config cfg;

    /**
     * TEST
     * Set testing-config value
     */
    cfg.set("testing-config", true);

    assert(cfg.get("testing-config") == true);

    /**
     * TEST
     * Remove testing-config value
     */
    cfg.remove("testing-config");

    assert(cfg.get("testing-config") == true);
}
