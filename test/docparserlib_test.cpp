#include <ctest.h>
#include <docparserlib/c_code_parser.h>
#include <string>
#include <vector>

CTEST(docparserlib_test, get_set_path_test)
{
    dp::CCodeParser parser;
    std::string pathExample = "D:/Git";

    parser.SetPath(pathExample);
    std::string actualPath = parser.GetPath();

    ASSERT_STR(pathExample.c_str(), actualPath.c_str());
}

CTEST(docparserlib_test, constructor_test)
{
    std::string pathExample = "D:/Git";

    dp::CCodeParser parser;
    ASSERT_STR("", parser.GetPath().c_str());

    dp::CCodeParser parserStringPath(pathExample);
    ASSERT_STR(pathExample.c_str(), parserStringPath.GetPath().c_str());

    dp::CCodeParser parserCharPath(pathExample.c_str());
    ASSERT_STR(pathExample.c_str(), parserCharPath.GetPath().c_str());
}

CTEST(docparserlib_test, pars_method_test)
{
    std::string actualPath = "example/test/code_example_test.cpp";
    dp::DocFunction expectedFunction(false, "std::ofstream", "hg::OpenFileWrite", "const std::string& path");
    dp::DocUnit expectedDocUnit(
            "Запись файла",
            "std::ofstream Поток на запись в файл",
            {"Примечание"},
            {dp::DocParam("path", "Путь к файлу")},
            {"std::invalid_argument Если файл нельзя открыть"},
            expectedFunction);

    dp::CCodeParser parser(actualPath);
    parser.Parse();
    dp::DocUnit actualDocUnit = parser.GetDocs().at(0);

    ASSERT_TRUE(expectedDocUnit == actualDocUnit);
}

CTEST(docparserlib_test, regex_comment_test)
{
    dp::CCodeParser parser;
    std::regex commentPattern = parser.GetCommentPattern();

    ASSERT_TRUE(std::regex_search("///@throw std::invalid_argument If one of args not a number", commentPattern));
    ASSERT_FALSE(std::regex_search("//@throw std::invalid_argument If one of args not a number", commentPattern));
    ASSERT_FALSE(std::regex_search("//_/@throw std::invalid_argument If one of args not a number", commentPattern));
}

CTEST(docparserlib_test, regex_brief_test)
{
    dp::CCodeParser parser;
    std::regex briefPattern = parser.GetBriefPattern();

    ASSERT_TRUE(std::regex_search("///@brief Add", briefPattern));
    ASSERT_TRUE(std::regex_search("//@brief Add", briefPattern));
    ASSERT_TRUE(std::regex_search("//_/@brief Add", briefPattern));
    ASSERT_FALSE(std::regex_search("/@bridef Add", briefPattern));
}

CTEST(docparserlib_test, regex_param_test)
{
    dp::CCodeParser parser;
    std::regex paramPattern = parser.GetParamPattern();

    ASSERT_TRUE(std::regex_search("///@param a First", paramPattern));
    ASSERT_TRUE(std::regex_search("//@param a First", paramPattern));
    ASSERT_TRUE(std::regex_search("//_/@param a First", paramPattern));
    ASSERT_FALSE(std::regex_search("/@paradsm a First", paramPattern));
}

CTEST(docparserlib_test, regex_return_test)
{
    dp::CCodeParser cCodeParser;
    std::regex returnPattern = cCodeParser.GetReturnPattern();

    ASSERT_TRUE(std::regex_search("///@return Sum a and b", returnPattern));
    ASSERT_TRUE(std::regex_search("//@return Sum a and b", returnPattern));
    ASSERT_TRUE(std::regex_search("//_/@return Sum a and b", returnPattern));
    ASSERT_FALSE(std::regex_search("/@returnds Sum a and b", returnPattern));
}

CTEST(docparserlib_test, regex_note_test)
{
    dp::CCodeParser parser;
    std::regex notePattern = parser.GetNotePattern();

    ASSERT_TRUE(std::regex_search("///@note notemonnte", notePattern));
    ASSERT_TRUE(std::regex_search("//@note notemonnte", notePattern));
    ASSERT_TRUE(std::regex_search("//_/@note notemonnte", notePattern));
    ASSERT_FALSE(std::regex_search("/@nosdte notemonsdndsdfte", notePattern));
}

CTEST(docparserlib_test, regex_throw_test)
{
    dp::CCodeParser parser;
    std::regex throwPattern = parser.GetThrowPattern();

    ASSERT_TRUE(std::regex_search("///@throw std::invalid_argument If one of args not a number", throwPattern));
    ASSERT_TRUE(std::regex_search("//@throw std::invalid_argument If one of args not a number", throwPattern));
    ASSERT_TRUE(std::regex_search("//_/@throw std::invalid_argument If one of args not a number", throwPattern));
    ASSERT_FALSE(std::regex_search("/@thrsdow std::invalid_argumensdfsdsdt If one of args not a number", throwPattern));
}

CTEST(docparserlib_test, regex_function_test)
{
    dp::CCodeParser parser;
    std::regex functionPattern = parser.GetFunctionPattern();

    ASSERT_TRUE(std::regex_search("const signed long long int sum(int a, int b, int c);", functionPattern));
    ASSERT_FALSE(std::regex_search("const signed long long int sum(int a, int b, int c;", functionPattern));
    ASSERT_FALSE(std::regex_search("const signed long long int sum int a, int b, int c);", functionPattern));
    ASSERT_TRUE(std::regex_search("dp::DocFunction::DocFunction(bool isConst);", functionPattern));
    ASSERT_TRUE(std::regex_search("vector<string> TemplateProcessor::ConvertDocParamsToStrings()", functionPattern));
}