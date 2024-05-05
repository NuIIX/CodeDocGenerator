#include "argument_parser.h"
#include <docparserlib/c_code_parser.h>
#include <fstream>
#include <htmlgeneratorlib/file_utils.h>
#include <htmlgeneratorlib/template_processor.h>
#include <iostream>

int main(int argc, char* argv[])
{
    const std::string docsPostfix = "_docs";
    const std::string outFileExt = ".txt";
    const std::string outDocsExt = ".html";
    const std::string errorHint = "Error: ";

    try {
        cdg::ArgumentParser argsParser(std::vector<std::string>(argv + 1, argv + argc));
        argsParser.Parse();

        if (argsParser.IsOnlyHelp()) {
            return 0;
        }

        if (argsParser.GetInPath().empty()) {
            throw std::invalid_argument("-c does not contain a path!");
        }

        std::string outPath;

        if (!argsParser.GetOutPath().empty()) {
            outPath = argsParser.GetOutPath() + docsPostfix;
        } else if (!argsParser.GetName().empty()) {
            outPath = argsParser.GetName() + docsPostfix;
        } else {
            outPath = argsParser.GetFileName() + docsPostfix;
        }

        dp::CCodeParser codeParser(argsParser.GetInPath());
        codeParser.Parse();

        if (argsParser.GetSaveFileState()) {
            std::ofstream outTextFile = hg::OpenFileWrite(outPath + outFileExt);
            codeParser.PrintDocs(outTextFile, argsParser.GetDecorator());
            outTextFile.close();
        }

        hg::TemplateProcessor templateProcessor(codeParser.GetDocs());

        if (!argsParser.GetName().empty()) {
            templateProcessor.SetHead(argsParser.GetName());
        }

        templateProcessor.CreateHtml(outPath + outDocsExt);
    } catch (const std::out_of_range& oorex) {
        std::cerr << errorHint << oorex.what() << std::endl;
        return 1;
    } catch (const std::runtime_error& reex) {
        std::cerr << errorHint << reex.what() << std::endl;
        return 1;
    } catch (const std::invalid_argument& iaex) {
        std::cerr << errorHint << iaex.what() << std::endl;
        return 1;
    }

    return 0;
}
