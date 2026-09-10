#include "includes/task.hpp"
#include <includes/command.hpp>
#include <includes/config.hpp>
#include <includes/engine.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    CommandArgs args = parseArguments(argc, argv);
    Config config;

    if (argc < 2 || args.command == UNKNOWN)
    {
        displayHelp(argv[0]);
        return 1;
    }

    switch (args.command)
    {
    case FIND:
    {
        if (args.query.empty())
        {
            std::cout << "Error: Missing search query.\n\n";
            displayHelp(argv[0]);
            return 1;
        }
        Task task;
        task.run(args.searchPath, args.query, config, args.excludePaths);
        return 0;
    }
    case HELP:
        displayHelp(argv[0]);
        return 0;

    case UNKNOWN:
    default:
        std::cout << "Unknown command.\n\n";
        displayHelp(argv[0]);
        return 1;
    }
}
