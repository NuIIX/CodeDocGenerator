#include <docparserlib/c_code_parser.h>
#include <iostream>

int main()
{
    dp::CCodeParser parser;

    try {
        parser.SetPath("example/docexample.c");
        parser.Parse();
        parser.PrintDocs();
    } catch (std::invalid_argument iaex) {
        std::cerr << iaex.what() << std::endl;
    }

    return 0;
}
