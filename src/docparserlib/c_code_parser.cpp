#include "c_code_parser.h"
#include "file_utils.h"

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

void dp::CCodeParser::SetPath(const char* cPath)
{
    _cPath = std::string(cPath);
}

const std::string& dp::CCodeParser::GetPath() const
{
    return _cPath;
}

const std::vector<dp::DocUnit>& dp::CCodeParser::GetDocs() const
{
    return _docData;
}

const std::regex& dp::CCodeParser::GetCommentPattern() const
{
    return _commentPattern;
}

const std::regex& dp::CCodeParser::GetBriefPattern() const
{
    return _briefPattern;
}

const std::regex& dp::CCodeParser::GetParamPattern() const
{
    return _paramPattern;
}

const std::regex& dp::CCodeParser::GetReturnPattern() const
{
    return _returnPattern;
}

const std::regex& dp::CCodeParser::GetNotePattern() const
{
    return _notePattern;
}

const std::regex& dp::CCodeParser::GetThrowPattern() const
{
    return _throwPattern;
}

const std::regex& dp::CCodeParser::GetFunctionPattern() const
{
    return _functionPattern;
}

void dp::CCodeParser::Parse()
{
    std::ifstream file = OpenFileRead(_cPath);
    std::string line;
    std::smatch fMatches, cMatches, pMatches, rMatches, nMatches, tMatches;
    DocUnit currentDocUnit;

    while (getline(file, line)) {
        if (std::regex_search(line, fMatches, _functionPattern)) {
            DocFunction function{
                    fMatches[1].length() != 0,
                    fMatches[2].str() + fMatches[3].str() + fMatches[4].str() + fMatches[5].str(),
                    fMatches[6].str(),
                    fMatches[7].str()};

            currentDocUnit.Function = function;
            _docData.push_back(currentDocUnit);
            currentDocUnit = DocUnit();
        } else if (std::regex_search(line, cMatches, _commentPattern)) {
            std::string comment = cMatches[1].str();

            if (std::regex_search(comment, pMatches, _paramPattern)) {
                DocParam param{pMatches[1].str(), pMatches[2].str()};
                currentDocUnit.Params.push_back(param);
            } else if (std::regex_search(comment, rMatches, _returnPattern)) {
                currentDocUnit.Return = rMatches[1].str();
            } else if (std::regex_search(comment, nMatches, _notePattern)) {
                currentDocUnit.Notes.push_back(nMatches[1].str());
            } else if (std::regex_search(comment, tMatches, _throwPattern)) {
                currentDocUnit.Throws.push_back(tMatches[1].str());
            }
        }
    }

    file.close();
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
