#include "c_code_parser.h"
#include <format>
#include <fstream>
#include <iostream>

dp::CCodeParser::CCodeParser(std::string cPathStr) : _cPath{cPathStr}
{
}

dp::CCodeParser::CCodeParser(char* cPath) : _cPath{std::string(cPath)}
{
}

dp::CCodeParser::CCodeParser()
{
}

std::string dp::CCodeParser::GetPath()
{
    return _cPath;
}

void dp::CCodeParser::SetPath(std::string cPathStr)
{
    _cPath = cPathStr;
}

void dp::CCodeParser::SetPath(char* cPath)
{
    _cPath = std::string(cPath);
}

std::vector<dp::DocUnit> dp::CCodeParser::GetDocs()
{
    return _docData;
}

std::vector<dp::DocUnit> dp::CCodeParser::Parse()
{
    std::ifstream file(_cPath);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to read file <" + _cPath + ">");
    }

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

    return _docData;
    file.close();
}

void dp::CCodeParser::PrintDocs()
{
    const std::string listMarker = "  ";
    for (const auto& docUnit : _docData) {
        std::cout << (docUnit.Name.length() != 0 ? "Name: " + docUnit.Name + "\n" : "");

        std::cout << std::format(
                "Function: {} [{}] [{}] [{}]",
                (docUnit.Function.isConst ? "const" : "not const"),
                docUnit.Function.Type,
                docUnit.Function.Name,
                docUnit.Function.VarParams)
                  << std::endl;

        std::cout << (docUnit.Return.length() != 0 ? "Return: " + docUnit.Return + "\n" : "");

        if (!docUnit.Params.empty()) {
            std::cout << "Params: " << std::endl;

            for (const auto& param : docUnit.Params) {
                std::cout << listMarker << param.Name << ": " << param.Description << std::endl;
            }
        }

        if (!docUnit.Notes.empty()) {
            std::cout << "Notes: " << std::endl;

            for (const auto& note : docUnit.Notes) {
                std::cout << listMarker << note << std::endl;
            }
        }

        if (!docUnit.Throws.empty()) {
            std::cout << "Throws: " << std::endl;

            for (const auto& throwStr : docUnit.Throws) {
                std::cout << listMarker << throwStr << std::endl;
            }
        }

        std::cout << std::endl;
    }
}
