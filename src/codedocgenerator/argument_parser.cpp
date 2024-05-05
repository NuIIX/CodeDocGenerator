#include "argument_parser.h"
#include <iostream>

cdg::ArgumentParser::ArgumentParser(const std::vector<std::string>& args) : _args(args)
{
}

cdg::ArgumentParser::ArgumentParser()
{
}

const std::string& cdg::ArgumentParser::GetOutPath() const
{
    return _outPath;
}

const std::string& cdg::ArgumentParser::GetInPath() const
{
    return _inPath;
}

const std::string& cdg::ArgumentParser::GetName() const
{
    return _name;
}

std::string cdg::ArgumentParser::GetFileName()
{
    const std::string delims = "/\\";

    std::string baseFilename = _inPath.substr(_inPath.find_last_of(delims) + 1);
    std::string::size_type const p(baseFilename.find_last_of('.'));
    std::string onlyFilename = baseFilename.substr(0, p);

    return onlyFilename;
}

const std::string& cdg::ArgumentParser::GetDecorator() const
{
    return _decorator;
}

const bool& cdg::ArgumentParser::GetSaveFileState() const
{
    return _saveFile;
}

const bool& cdg::ArgumentParser::IsOnlyHelp() const
{
    return _isOnlyHelp;
}

void cdg::ArgumentParser::PrintHelp()
{
    std::cout << std::endl
              << "Usage:" << std::endl
              << std::endl
              << "  cdg [-c <path>]             : HTML will be created in the current directory" << std::endl
              << "  cdg <path>                  : HTML will be created in the current directory" << std::endl
              << "  cdg -c <path> -f            : HTML and TXT will be created in the current directory" << std::endl
              << "  cdg -c <path> -f -o <hpath> : HTML and TXT will be created along the <hpath> path" << std::endl
              << std::endl
              << "Commands:" << std::endl
              << std::endl
              << "  cdg <path>     : Generating an HTML file using the specified code path  (required)" << std::endl
              << "  -c <path>      : Specifying the path to the code                        (required)" << std::endl
              << "  -f <decorator> : Additionally save as a text file                       (optional)" << std::endl
              << "  -o <path>      : Specifying the path for the HTML output file           (optional)" << std::endl
              << "  -n <name>      : Specifying the title of the documentation              (optional)" << std::endl
              << "  -h             : Displaying a hint for all commands                     (optional)" << std::endl
              << std::endl
              << "<path>      - path without specifying an extension (except -c <path>)" << std::endl
              << "<decorator> - optional list marker" << std::endl
              << "<name>      - the title of the documentation (and the name of the file)" << std::endl;
}

void cdg::ArgumentParser::CheckArgsNext(const size_t& it, const std::string& errorWhat)
{
    if (it + 1 >= _args.size()) {
        throw std::out_of_range(errorWhat);
    }
}

void cdg::ArgumentParser::Parse()
{
    if (_args.empty()) {
        throw std::runtime_error("Write -h for help");
    }

    if (_args.size() == 1 && _args.at(0) != "-h") {
        _inPath = _args.at(0);
        return;
    }

    for (size_t it = 0; it < _args.size(); it++) {
        if (_args.at(it) == "-h") {
            PrintHelp();
            _isOnlyHelp = true;
            return;
        } else if (_args.at(it) == "-f") {
            _saveFile = true;
            CheckArgsNext(it, "Usage -f <decorator>");
            _decorator = _args.at(it + 1);
        } else if (_args.at(it) == "-c") {
            CheckArgsNext(it, "Usage -c <path>");
            _inPath = _args.at(it + 1);
        } else if (_args.at(it) == "-o") {
            CheckArgsNext(it, "Usage -o <path>");
            _outPath = _args.at(it + 1);
        } else if (_args.at(it) == "-n") {
            CheckArgsNext(it, "Usage -n <name>");
            _name = _args.at(it + 1);
        }
    }

    _isOnlyHelp = false;
}
