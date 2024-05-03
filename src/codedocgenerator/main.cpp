#include "argument_parser.h"
#include <docparserlib/c_code_parser.h>
#include <fstream>
#include <htmlgeneratorlib/file_utils.h>
#include <htmlgeneratorlib/template_processor.h>
#include <iostream>

int main(int argc, char* argv[])
{
    try {
        cdg::ArgumentParser argsParser(std::vector<std::string>(argv + 1, argv + argc));
        argsParser.Parse();

        if (argsParser.GetInPath().empty()) {
            throw std::invalid_argument("-c does not contain a path!");
        }

        std::string outPath;

        if (!argsParser.GetOutPath().empty()) {
            outPath = argsParser.GetOutPath() + "_docs";
        } else if (!argsParser.GetName().empty()) {
            outPath = argsParser.GetName() + "_docs";
        } else {
            outPath = argsParser.GetFileName() + "_docs";
        }

        dp::CCodeParser codeParser(argsParser.GetInPath());
        codeParser.Parse();

        if (argsParser.GetSaveFileState()) {
            std::ofstream outTextFile = hg::OpenFileWrite(outPath + ".txt");
            codeParser.PrintDocs(outTextFile);
            outTextFile.close();
        }

        hg::TemplateProcessor templateProcessor(codeParser.GetDocs());

        if (!argsParser.GetName().empty()) {
            templateProcessor.SetHead(argsParser.GetName());
        }

        templateProcessor.CreateHtml(outPath + ".html");
    } catch (const std::out_of_range& oorex) {
        std::cerr << "Error: " << oorex.what();
        return 1;
    } catch (const std::runtime_error& reex) {
        std::cerr << "Error: " << reex.what();
        return 1;
    } catch (const std::invalid_argument& iaex) {
        std::cerr << "Error: " << iaex.what();
        return 1;
    }

    return 0;
}
