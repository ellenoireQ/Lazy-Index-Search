#include <includes/config.hpp>

void config::Config::set(const char *__cfg, bool state)
{
    this->cfg.emplace(__cfg, state);
}

bool config::Config::get(const char *__key)
{
    auto it = this->cfg.find(__key);

    if (it != this->cfg.end())
    {
        return it->second;
    }
    return false;
}

void config::Config::remove(const char *__key)
{
    auto it = this->cfg.find(__key);

    if (it != this->cfg.end())
    {
        this->cfg.erase(it);
    }
}