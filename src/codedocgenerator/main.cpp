#include <docparserlib/c_code_parser.h>
#include <htmlgeneratorlib/template_processor.h>
#include <iostream>

int main()
{
    dp::CCodeParser parser;
    hg::TemplateProcessor templater;
    std::vector<dp::DocUnit> docData;

    try {
        parser.SetPath("example/docexample.c");
        docData = parser.Parse();
        templater.SetDocs(docData);
        templater.CreateHtml("output.html");
    } catch (std::invalid_argument iaex) {
        std::cerr << iaex.what() << std::endl;
    }

    return 0;
}
