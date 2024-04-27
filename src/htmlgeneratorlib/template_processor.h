#pragma once

#ifndef TEMPLATEPROCESSOR_H
#define TEMPLATEPROCESSOR_H

#include <docparserlib/doc_unit.h>
#include <map>
#include <vector>

namespace hg {
    class TemplateProcessor {
    private:
        std::vector<dp::DocUnit> _docData;
        const std::string _templateMainPath;
        const std::string _templateTablePath;

        static std::string ReplaceTags(std::string&, std::map<std::string, std::string>);

    public:
        TemplateProcessor(std::vector<dp::DocUnit>&);
        TemplateProcessor();

        void SetDocs(std::vector<dp::DocUnit>&);
        std::vector<dp::DocUnit>& GetDocs();

        void CreateHtml(std::map<std::string, std::string>, std::string);
    };
}

#endif // !TEMPLATEPROCESSOR_H
