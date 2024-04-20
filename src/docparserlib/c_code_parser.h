#pragma once

#ifndef CCODEPARSER_H
#define CCODEPARSER_H

#include <string>
#include <vector>
#include <regex>
#include "doc_unit.h"

namespace dp {
    class CCodeParser {
        private:
            std::string _cPath = "";
            std::vector<dp::DocUnit> _docData;

            const std::regex _commentPattern = regex(R"(\/\/\/(.*))");
            const std::regex _briefPattern = regex(R"(@brief\s+(.+))");
            const std::regex _paramPattern = regex(R"(@param\s+(\w+)\s+(.*))");
            const std::regex _returnPattern = regex(R"(@return\s+(.+))");
            const std::regex _notePattern = regex(R"(@note\s+(.+))");
            const std::regex _throwPattern = regex(R"(@throw\s+(.+))");
            const std::regex _functionPattern = regex(R"((const\s+)?(unsigned\s+|signed\s+)?(long\s+)?(long\s+)?(\w+)\s+(\w+)\s*\((.*?)\)\s*[\;\{])");
        public:
            CCodeParser(std::string);
            CCodeParser(char*);
            CCodeParser();

            std::string GetPath();
            void SetPath(std::string);
            void SetPath(char*);
            std::vector<DocUnit> GetDocs();

            std::vector<DocUnit> Parse();
            void PrintDocs();
    };
}

#endif // !CCODEPARSER_H