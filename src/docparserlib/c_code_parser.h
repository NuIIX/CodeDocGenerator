#pragma once

#ifndef CCODEPARSER_H
#define CCODEPARSER_H

#include "doc_unit.h"
#include <regex>
#include <string>
#include <vector>

namespace dp {
    class CCodeParser {
    private:
        std::string _cPath = "";
        std::vector<dp::DocUnit> _docData;

        const std::regex _commentPattern = std::regex(R"(\/\/\/(.*))");
        const std::regex _briefPattern = std::regex(R"(@brief\s+(.+))");
        const std::regex _paramPattern = std::regex(R"(@param\s+(\w+)\s+(.*))");
        const std::regex _returnPattern = std::regex(R"(@return\s+(.+))");
        const std::regex _notePattern = std::regex(R"(@note\s+(.+))");
        const std::regex _throwPattern = std::regex(R"(@throw\s+(.+))");
        const std::regex _functionPattern = std::regex(
                R"((const\s+)?(unsigned\s+|signed\s+)?(long\s+)?(long\s+)?(\w+)\s+(\w+)\s*\((.*?)\)\s*[\;\{])");

    public:
        CCodeParser(std::string);
        CCodeParser(const char*);
        CCodeParser();

        std::string GetPath();
        void SetPath(std::string);
        void SetPath(const char*);
        std::vector<DocUnit> GetDocs();

        std::vector<DocUnit> Parse();
        void PrintDocs();
    };
}

#endif // !CCODEPARSER_H
