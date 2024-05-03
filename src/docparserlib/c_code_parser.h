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
        CCodeParser(const std::string&);
        CCodeParser(const char*);
        CCodeParser();

        void SetPath(const std::string&);
        const std::string& GetPath() const;
        void SetPath(const char*);
        const std::vector<DocUnit>& GetDocs() const;
        const std::regex& GetCommentPattern() const;
        const std::regex& GetBriefPattern() const;
        const std::regex& GetParamPattern() const;
        const std::regex& GetReturnPattern() const;
        const std::regex& GetNotePattern() const;
        const std::regex& GetThrowPattern() const;
        const std::regex& GetFunctionPattern() const;

        std::vector<DocUnit> Parse();
        void PrintDocs(std::ostream&, const std::string& = "  ");
    };
}

#endif // !CCODEPARSER_H
