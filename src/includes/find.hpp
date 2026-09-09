#include <filesystem>
#include <includes/config.hpp>

namespace fclasses
{
    namespace fs = std::filesystem;
    /** finding file based by name */
    void find(const char *tgetf, Config &config);
};
