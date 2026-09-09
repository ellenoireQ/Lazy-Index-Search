#ifndef COMMAND_HEADER_HPP
#define COMMAND_HEADER_HPP

#include <string>

enum Command
{
    FIND,
    HELP,
    UNKNOWN
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

#endif // COMMAND_HEADER_HPP