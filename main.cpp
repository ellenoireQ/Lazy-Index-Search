#include <iostream>
#include <string>
#include <includes/command.hpp>
#include <includes/engine.hpp>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [--find|-f] <query>\n";
        return 1;
    }

    const std::string command = argv[1];

    switch (parseCommand(command))
    {
    case FIND:
        if (argc < 3)
        {
            std::cout << "Missing search query.\n";
            std::cout << "Usage: " << argv[0] << " [--find|-f] <query>\n";
            return 1;
        }

        engine::search("/", argv[2]);
        return 0;

    case HELP:
        std::cout << "Usage: " << argv[0] << " [--find|-f] <query>\n";
        return 0;

    case UNKNOWN:
    default:
        std::cout << "Unknown command: " << command << "\n";
        std::cout << "Usage: " << argv[0] << " [--find|-f] <query>\n";
        return 1;
    }
}
