#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <unordered_map>
#include <string>

class Config
{
private:
    std::unordered_map<std::string, bool> cfg;

public:
    void set(const char *__cfg, bool state);
    bool get(const char *__key);
    void remove(const char *__key);
};

#endif // CONFIG_HPP