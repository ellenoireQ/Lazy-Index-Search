#ifndef COMMAND_HEADER_HPP
#define COMMAND_HEADER_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

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
    std::vector<std::string> excludePaths;
};

/**
 * Split string by delimiter
 * @param str String to split
 * @param delimiter Delimiter character
 * @return Vector of split strings
 */
static std::vector<std::string> splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        token = str.substr(start, end - start);
        if (!token.empty())
        {
            tokens.push_back(token);
        }
        start = end + 1;
        end = str.find(delimiter, start);
    }

    token = str.substr(start);
    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * Parse argument with format --key=value or --key="value"
 * @param arg Full argument string
 * @param key Expected key (e.g., "--exclude-path")
 * @return Value string or empty if not matching
 */
static std::string parseKeyValue(const std::string &arg, const std::string &key)
{
    if (arg.find(key + "=") == 0)
    {
        std::string value = arg.substr(key.length() + 1);

        if (value.length() >= 2 && value.front() == '"' && value.back() == '"')
        {
            value = value.substr(1, value.length() - 2);
        }

        return value;
    }
    return "";
}

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
        else if (arg.find("--exclude-path=") == 0)
        {
            std::string value = parseKeyValue(arg, "--exclude-path");
            if (!value.empty())
            {
                args.excludePaths = splitString(value, ',');
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
    std::cout << "  --path, -p <path>              Set search path (default: /)\n";
    std::cout << "  --exclude-path=\"path1,path2\"   Exclude paths from search (comma-separated)\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " --find file.cpp\n";
    std::cout << "  " << programName << " --find file.cpp --path /usr\n";
    std::cout << "  " << programName << " --find file.cpp --exclude-path=\"/usr,/var\"\n";
    std::cout << "  " << programName << " --find file.cpp --path /home --exclude-path=\"/home/user/.cache\"\n";
}

#endif // COMMAND_HEADER_HPP
