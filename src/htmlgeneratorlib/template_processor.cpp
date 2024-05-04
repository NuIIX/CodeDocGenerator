#include "template_processor.h"
#include "file_utils.h"
#include <regex>

hg::TemplateProcessor::TemplateProcessor(const std::vector<dp::DocUnit>& docData, const std::string& head)
    : _docData(docData), _head(head)
{
}

hg::TemplateProcessor::TemplateProcessor(const std::vector<dp::DocUnit>& docData) : _docData(docData)
{
}

hg::TemplateProcessor::TemplateProcessor()
{
}

void hg::TemplateProcessor::SetDocs(const std::vector<dp::DocUnit>& docData)
{
    _docData = docData;
}

void hg::TemplateProcessor::SetHead(const std::string& head)
{
    _head = head;
}

const std::vector<dp::DocUnit>& hg::TemplateProcessor::GetDocs() const
{
    return _docData;
}

std::string
hg::TemplateProcessor::ReplaceTags(const std::string& shmtl, const std::map<std::string, std::string>& tagToValueMap)
{
    std::string output = shmtl;
    const std::regex tagPattern(R"(\{\{\s*(.*)\s*\}\})");

    std::sregex_iterator it(shmtl.begin(), shmtl.end(), tagPattern);
    std::sregex_iterator end;

    for (; it != end; ++it) {
        std::smatch match = *it;
        std::string tag = match.str(1);

        if (tagToValueMap.count(tag) > 0) {
            output = ReplaceTag(output, tag, tagToValueMap.at(tag));
        }
    }

    return output;
}

std::string
hg::TemplateProcessor::ReplaceTag(const std::string& shmtl, const std::string& tag, const std::string& input)
{
    std::regex tagPattern(R"(\{\{)" + tag + R"(\}\})");

    std::string result = shmtl;
    result = std::regex_replace(result, tagPattern, input);

    return result;
}

std::string hg::TemplateProcessor::GetFunctionStr(const dp::DocFunction& func)
{
    std::string isConstStr = func.isConst ? "[const]" : "";

    std::string result = isConstStr + "[" + func.Type + "][" + func.Name + "][" + func.VarParams + "] ";

    return result;
}

std::string hg::TemplateProcessor::ConvertListToHtml(const std::string& name, const std::vector<std::string>& listItems)
{
    if (listItems.empty()) {
        return "";
    }

    if (listItems.at(0) == "") {
        return "";
    }

    std::string htmlListStr = "<h2>" + name + "</h2>\n";

    for (const auto& item : listItems) {
        htmlListStr.append("<p>").append(item).append("</p>\n");
    }

    return htmlListStr;
}

std::vector<std::string> hg::TemplateProcessor::ConvertDocParamsToStrings(const std::vector<dp::DocParam>& params)
{
    std::vector<std::string> docParamsStr;

    for (const auto& param : params) {
        docParamsStr.push_back(param.Name + ": " + param.Description);
    }

    return docParamsStr;
}

std::string hg::TemplateProcessor::ProcessBlockTemplate(const dp::DocUnit& docUnit, std::string blockContent)
{
    std::map<std::string, std::string> tagToValueMap
            = {{"FuncName", docUnit.Function.Name},
               {"FuncFull", GetFunctionStr(docUnit.Function)},
               {"FuncBrief", docUnit.Brief},
               {"FuncData", ProcessFuncTemplate(docUnit)}};

    std::string blocks = ReplaceTags(blockContent, tagToValueMap);

    return blocks;
}

std::string hg::TemplateProcessor::ProcessFuncTemplate(const dp::DocUnit& docUnit)
{
    std::string htmlFuncStr = ConvertListToHtml("Return", {docUnit.Return});

    htmlFuncStr.append(ConvertListToHtml("Notes", docUnit.Notes));
    htmlFuncStr.append(ConvertListToHtml("Throws", docUnit.Throws));
    htmlFuncStr.append(ConvertListToHtml("Params", ConvertDocParamsToStrings(docUnit.Params)));

    return htmlFuncStr;
}

void hg::TemplateProcessor::CreateHtml(std::string outPath)
{
    auto templateMainFile = OpenFileRead(_templateMainPath);
    auto templateBlockFile = OpenFileRead(_templateBlockPath);

    const std::string mainContent((std::istreambuf_iterator<char>(templateMainFile)), std::istreambuf_iterator<char>());
    const std::string blockContent(
            (std::istreambuf_iterator<char>(templateBlockFile)), std::istreambuf_iterator<char>());

    templateMainFile.close();
    templateBlockFile.close();

    std::string processedContent = mainContent;
    std::string processedBlockContent;

    for (const auto& docUnit : _docData) {
        processedBlockContent.append(ProcessBlockTemplate(docUnit, blockContent)).append("\n");
    }

    processedContent = ReplaceTag(processedContent, "Head", _head.size() == 0 ? "Documentation" : _head);
    processedContent = ReplaceTag(processedContent, "Block", processedBlockContent);

    auto outFile = OpenFileWrite(outPath);

    outFile << processedContent;
    outFile.close();
}
