#include <iostream>
#include <string>
#include <includes/command.hpp>
#include <includes/engine.hpp>

int main(int argc, char *argv[])
{
    CommandArgs args = parseArguments(argc, argv);

    if (argc < 2 || args.command == UNKNOWN)
    {
        displayHelp(argv[0]);
        return 1;
    }

    switch (args.command)
    {
    case FIND:
        if (args.query.empty())
        {
            std::cout << "Error: Missing search query.\n\n";
            displayHelp(argv[0]);
            return 1;
        }

        engine::search(args.searchPath, args.query);
        return 0;

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