#include <docparserlib/c_code_parser.h>
#include <fstream>
#include <htmlgeneratorlib/file_utils.h>
#include <htmlgeneratorlib/template_processor.h>
#include <iostream>

int main()
{
    dp::CCodeParser parser;
    hg::TemplateProcessor templater;
    std::vector<dp::DocUnit> docData;

    try {
        parser.SetPath("example/docexample.cpp");
        parser.Parse();
        docData = parser.GetDocs();
        templater.SetDocs(docData);
        templater.CreateHtml("output.html");
    } catch (const std::invalid_argument& iaex) {
        std::cerr << iaex.what() << std::endl;
    }

    return 0;
}
