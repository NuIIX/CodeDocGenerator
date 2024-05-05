#pragma once

#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <string>
#include <vector>

namespace cdg {
    class ArgumentParser {
    private:
        std::vector<std::string> _args;
        std::string _outPath;
        std::string _inPath;
        std::string _name;
        std::string _decorator;
        bool _saveFile = false;
        bool _isOnlyHelp = false;

        void PrintHelp();
        void CheckArgsNext(const size_t&, const std::string&);

    public:
        ArgumentParser(const std::vector<std::string>&);
        ArgumentParser();

        const std::string& GetOutPath() const;
        const std::string& GetInPath() const;
        const std::string& GetName() const;
        std::string GetFileName();
        const std::string& GetDecorator() const;
        const bool& GetSaveFileState() const;
        const bool& IsOnlyHelp() const;

        void Parse();
    };
}

#endif // !ARGUMENTPARSER_H
