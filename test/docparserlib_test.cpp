#include <ctest.h>
#include <docparserlib/c_code_parser.h>
#include <string>
#include <vector>

CTEST(docparserlib_test, get_set_path_test)
{
    dp::CCodeParser cCodeParser;
    std::string path = "D:/Git";

    cCodeParser.SetPath(path);
    std::string resultPath = cCodeParser.GetPath();

    ASSERT_STR(path.c_str(), resultPath.c_str());
}

CTEST(docparserlib_test, designer_test)
{
    std::string path = "D:/Git";
    std::string resultPath = "";
    dp::CCodeParser cCodeParser = dp::CCodeParser();
    dp::CCodeParser cCodeParserStringPath = dp::CCodeParser(path);
    dp::CCodeParser cCodeParserCharPath = dp::CCodeParser(path.c_str());

    resultPath = cCodeParser.GetPath();
    ASSERT_STR("", resultPath.c_str());

    resultPath = cCodeParserStringPath.GetPath();
    ASSERT_STR(path.c_str(), resultPath.c_str());

    resultPath = cCodeParserCharPath.GetPath();
    ASSERT_STR(path.c_str(), resultPath.c_str());
}

CTEST(docparserlib_test, pars_method_test)
{
    std::string path = "example/docexample.cpp";
    dp::DocUnit exampleDocUnit
            = {"Add",
               "Sum a and b",
               {"notemonnte", "note2"},
               {{"a", "First"}, {"b", "Second"}, {"c", "Third"}},
               {"std::invalid_argument If one of args not a number"},
               {true, "signed long long int", "sum2", "int a, int b, int c"}};

    dp::CCodeParser cCodeParser = dp::CCodeParser(path);
    cCodeParser.Parse();
    dp::DocUnit resultDocUnit = cCodeParser.GetDocs().at(1);

    ASSERT_TRUE(exampleDocUnit == resultDocUnit);
}

CTEST(docparserlib_test, regex_comment_test)
{
    dp::CCodeParser cCodeParser;
    std::regex commentPattern = cCodeParser.GetCommentPattern();

    std::string exampleReg = "///@throw std::invalid_argument If one of args not a number";
    ASSERT_TRUE(std::regex_search(exampleReg, commentPattern));

    exampleReg = "//@throw std::invalid_argument If one of args not a number";
    ASSERT_FALSE(std::regex_search(exampleReg, commentPattern));

    exampleReg = "//_/@throw std::invalid_argument If one of args not a number";
    ASSERT_FALSE(std::regex_search(exampleReg, commentPattern));
}

CTEST(docparserlib_test, regex_brief_test)
{
    dp::CCodeParser cCodeParser;
    std::regex briefPattern = cCodeParser.GetBriefPattern();

    std::string exampleReg = "///@brief Add";
    ASSERT_TRUE(std::regex_search(exampleReg, briefPattern));

    exampleReg = "//@brief Add";
    ASSERT_TRUE(std::regex_search(exampleReg, briefPattern));

    exampleReg = "//_/@brief Add";
    ASSERT_TRUE(std::regex_search(exampleReg, briefPattern));

    exampleReg = "/@bridef Add";
    ASSERT_FALSE(std::regex_search(exampleReg, briefPattern));
}

CTEST(docparserlib_test, regex_param_test)
{
    dp::CCodeParser cCodeParser;
    std::regex paramPattern = cCodeParser.GetParamPattern();

    std::string exampleReg = "///@param a First";
    ASSERT_TRUE(std::regex_search(exampleReg, paramPattern));

    exampleReg = "//@param a First";
    ASSERT_TRUE(std::regex_search(exampleReg, paramPattern));

    exampleReg = "//_/@param a First";
    ASSERT_TRUE(std::regex_search(exampleReg, paramPattern));

    exampleReg = "/@paradsm a First";
    ASSERT_FALSE(std::regex_search(exampleReg, paramPattern));
}

CTEST(docparserlib_test, regex_return_test)
{
    dp::CCodeParser cCodeParser;
    std::regex returnPattern = cCodeParser.GetReturnPattern();

    std::string exampleReg = "///@return Sum a and b";
    ASSERT_TRUE(std::regex_search(exampleReg, returnPattern));

    exampleReg = "//@return Sum a and b";
    ASSERT_TRUE(std::regex_search(exampleReg, returnPattern));

    exampleReg = "//_/@return Sum a and b";
    ASSERT_TRUE(std::regex_search(exampleReg, returnPattern));

    exampleReg = "/@returnds Sum a and b";
    ASSERT_FALSE(std::regex_search(exampleReg, returnPattern));
}

CTEST(docparserlib_test, regex_note_test)
{
    dp::CCodeParser cCodeParser;
    std::regex notePattern = cCodeParser.GetNotePattern();

    std::string exampleReg = "///@note notemonnte";
    ASSERT_TRUE(std::regex_search(exampleReg, notePattern));

    exampleReg = "//@note notemonnte";
    ASSERT_TRUE(std::regex_search(exampleReg, notePattern));

    exampleReg = "//_/@note notemonnte";
    ASSERT_TRUE(std::regex_search(exampleReg, notePattern));

    exampleReg = "/@nosdte notemonsdndsdfte";
    ASSERT_FALSE(std::regex_search(exampleReg, notePattern));
}

CTEST(docparserlib_test, regex_throw_test)
{
    dp::CCodeParser cCodeParser;
    std::regex throwPattern = cCodeParser.GetThrowPattern();

    std::string exampleReg = "///@throw std::invalid_argument If one of args not a number";
    ASSERT_TRUE(std::regex_search(exampleReg, throwPattern));

    exampleReg = "//@throw std::invalid_argument If one of args not a number";
    ASSERT_TRUE(std::regex_search(exampleReg, throwPattern));

    exampleReg = "//_/@throw std::invalid_argument If one of args not a number";
    ASSERT_TRUE(std::regex_search(exampleReg, throwPattern));

    exampleReg = "/@thrsdow std::invalid_argumensdfsdsdt If one of args not a number";
    ASSERT_FALSE(std::regex_search(exampleReg, throwPattern));
}

CTEST(docparserlib_test, regex_function_test)
{
    dp::CCodeParser cCodeParser;
    std::regex functionPattern = cCodeParser.GetFunctionPattern();

    std::string exampleReg = "const signed long long int sum(int a, int b, int c);";
    ASSERT_TRUE(std::regex_search(exampleReg, functionPattern));

    exampleReg = "const signed long long int sum(int a, int b, int c;";
    ASSERT_FALSE(std::regex_search(exampleReg, functionPattern));

    exampleReg = "const signed long long int sum int a, int b, int c);";
    ASSERT_FALSE(std::regex_search(exampleReg, functionPattern));

    exampleReg = "const signed long long |(int sum int a, int b, int c);";
    ASSERT_FALSE(std::regex_search(exampleReg, functionPattern));
}
