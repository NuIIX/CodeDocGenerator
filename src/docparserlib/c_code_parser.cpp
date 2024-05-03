#include "c_code_parser.h"
#include "file_utils.h"
#include <iostream>

dp::CCodeParser::CCodeParser(const std::string& cPathStr) : _cPath{cPathStr}
{
}

dp::CCodeParser::CCodeParser(const char* cPath) : _cPath{std::string(cPath)}
{
}

dp::CCodeParser::CCodeParser()
{
}

void dp::CCodeParser::SetPath(const std::string& cPathStr)
{
    _cPath = cPathStr;
}

const std::string& dp::CCodeParser::GetPath() const
{
    return _cPath;
}

void dp::CCodeParser::SetPath(const char* cPath)
{
    _cPath = std::string(cPath);
}

const std::vector<dp::DocUnit>& dp::CCodeParser::GetDocs() const
{
    return _docData;
}

std::vector<dp::DocUnit> dp::CCodeParser::Parse()
{
    std::ifstream file = OpenFileRead(_cPath);

    std::string line;
    std::smatch matches;
    DocUnit currentDocUnit;

    while (getline(file, line)) {
        if (std::regex_search(line, matches, _commentPattern)) {
            std::string comment = matches[1].str();

            if (std::regex_search(comment, matches, _paramPattern)) {
                DocParam param{matches[1].str(), matches[2].str()};

                currentDocUnit.Params.push_back(param);
            } else if (std::regex_search(comment, matches, _returnPattern)) {
                currentDocUnit.Return = matches[1].str();
            } else if (std::regex_search(comment, matches, _notePattern)) {
                currentDocUnit.Notes.push_back(matches[1].str());
            } else if (std::regex_search(comment, matches, _throwPattern)) {
                currentDocUnit.Throws.push_back(matches[1].str());
            }
        } else if (std::regex_search(line, matches, _functionPattern)) {
            DocFunction function{
                    matches[1].length() != 0,
                    matches[2].str() + matches[3].str() + matches[4].str() + matches[5].str(),
                    matches[6].str(),
                    matches[7].str()};

            currentDocUnit.Function = function;

            _docData.push_back(currentDocUnit);
            currentDocUnit = DocUnit();
        }
    }

    file.close();
    return _docData;
}

void dp::CCodeParser::PrintDocs(std::ostream& stream, const std::string& listDecorator)
{
    for (const auto& docUnit : _docData) {
        stream << "Function: " << "[" << (docUnit.Function.isConst ? "const" : "not const") << "] ["
               << docUnit.Function.Type << "] [" << docUnit.Function.Name << "] [" << docUnit.Function.VarParams << "]"
               << std::endl;

        stream << (docUnit.Return.length() != 0 ? "Return: " + docUnit.Return + "\n" : "");

        if (!docUnit.Params.empty()) {
            stream << "Params: " << std::endl;

            for (const auto& param : docUnit.Params) {
                stream << listDecorator << param.Name << ": " << param.Description << std::endl;
            }
        }

        if (!docUnit.Notes.empty()) {
            stream << "Notes: " << std::endl;

            for (const auto& note : docUnit.Notes) {
                stream << listDecorator << note << std::endl;
            }
        }

        if (!docUnit.Throws.empty()) {
            stream << "Throws: " << std::endl;

            for (const auto& throwStr : docUnit.Throws) {
                stream << listDecorator << throwStr << std::endl;
            }
        }

        stream << std::endl;
    }
}
