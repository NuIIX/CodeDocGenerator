#pragma once

#ifndef TEMPLATEPROCESSOR_H
#define TEMPLATEPROCESSOR_H

#include <docparserlib/doc_unit.h>
#include <map>
#include <string>
#include <vector>

namespace hg {
    class TemplateProcessor {
    private:
        std::vector<dp::DocUnit> _docData;
        std::string _head;

        const std::string _templateMainPath = "data/main_template.html";
        const std::string _templateListItemPath = "data/list_item.html";
        const std::string _templateBlockPath = "data/block_template.html";

        static std::string ReplaceTags(const std::string&, const std::map<std::string, std::string>&);
        static std::string ReplaceTag(const std::string&, const std::string&, const std::string&);

        std::string GetFunctionStr(const dp::DocFunction&);
        std::string ConvertListToHtml(const std::string&, const std::vector<std::string>&);
        std::vector<std::string> ConvertDocParamsToStrings(const std::vector<dp::DocParam>&);

        std::string ProcessBlockTemplate(const dp::DocUnit&, std::string);
        std::string ProcessFuncTemplate(const dp::DocUnit&);

    public:
        TemplateProcessor(std::vector<dp::DocUnit>&, const std::string);
        TemplateProcessor(std::vector<dp::DocUnit>&);
        TemplateProcessor();

        void SetDocs(const std::vector<dp::DocUnit>&);
        void SetHead(const std::string&);
        const std::vector<dp::DocUnit>& GetDocs() const;

        void CreateHtml(std::string);
    };
}

#endif // !TEMPLATEPROCESSOR_H
