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
    std::string path = "example/docexample.c";
    dp::DocUnit exampleDocUnit
            = {"Sum a and b",
               {"notemonnte", "note2"},
               {{"a", "First"}, {"b", "Second"}, {"c", "Third"}},
               {"std::invalid_argument If one of args not a number"},
               {true, "signed long long int", "sum2", "int a, int b, int c"}};

    dp::CCodeParser cCodeParser = dp::CCodeParser(path);

    dp::DocUnit resultDocUnit = cCodeParser.Parse()[1];

    ASSERT_TRUE(exampleDocUnit.Return == resultDocUnit.Return);

    for (size_t i = 0; i < resultDocUnit.Notes.size(); i++) {
        ASSERT_TRUE(exampleDocUnit.Notes[i] == resultDocUnit.Notes[i]);
    }

    for (size_t i = 0; i < resultDocUnit.Params.size(); i++) {
        ASSERT_TRUE(exampleDocUnit.Params[i].Name == resultDocUnit.Params[i].Name);
        ASSERT_TRUE(exampleDocUnit.Params[i].Description == resultDocUnit.Params[i].Description);
    }

    for (size_t i = 0; i < resultDocUnit.Throws.size(); i++) {
        ASSERT_TRUE(exampleDocUnit.Throws[i] == resultDocUnit.Throws[i]);
    }

    ASSERT_TRUE(exampleDocUnit.Function.isConst == resultDocUnit.Function.isConst);
    ASSERT_TRUE(exampleDocUnit.Function.Name == resultDocUnit.Function.Name);
    ASSERT_TRUE(exampleDocUnit.Function.Type == resultDocUnit.Function.Type);
    ASSERT_TRUE(exampleDocUnit.Function.VarParams == resultDocUnit.Function.VarParams);
}
