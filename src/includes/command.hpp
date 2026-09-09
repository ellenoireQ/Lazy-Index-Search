#ifndef COMMAND_HEADER_HPP
#define COMMAND_HEADER_HPP

#include <string>
#include <vector>
#include <map>

enum Command
{
    FIND,
    HELP,
    UNKNOWN
};

struct CommandArgs
{
    Command command = UNKNOWN;
    std::string query;
    std::string searchPath = "/";
};

/**
 * @param command Get argv string
 */
static Command parseCommand(const std::string &command)
{
    if (command == "--find" || command == "-f")
    {
        return FIND;
    }

    if (command == "--help" || command == "-h")
    {
        return HELP;
    }

    return UNKNOWN;
}

/**
 * Parse command line arguments
 * @param argc Argument count
 * @param argv Argument values
 * @return CommandArgs structure with parsed arguments
 */
static CommandArgs parseArguments(int argc, char *argv[])
{
    CommandArgs args;

    if (argc < 2)
    {
        return args;
    }

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--find" || arg == "-f")
        {
            args.command = FIND;
            if (i + 1 < argc)
            {
                args.query = argv[++i];
            }
        }
        else if (arg == "--help" || arg == "-h")
        {
            args.command = HELP;
        }
        else if (arg == "--path" || arg == "-p")
        {
            if (i + 1 < argc)
            {
                args.searchPath = argv[++i];
            }
        }
    }

    return args;
}

/**
 * Display help message
 */
static void displayHelp(const std::string &programName)
{
    std::cout << "Usage: " << programName << " [OPTIONS]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  --find, -f <query>      Search for files matching query\n";
    std::cout << "  --help, -h              Display this help message\n\n";
    std::cout << "Options:\n";
    std::cout << "  --path, -p <path>       Set search path (default: /)\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " --find file.cpp\n";
    std::cout << "  " << programName << " --find file.cpp --path /usr\n";
}

#endif // COMMAND_HEADER_HPP