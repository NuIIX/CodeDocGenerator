#include "doc_function.h"

dp::DocFunction::DocFunction()
{
}

dp::DocFunction::DocFunction(bool isConst, const std::string& type, const std::string& name, const std::string& params)
    : IsConst(isConst), Type(type), Name(name), VarParams(params)
{
}

bool dp::DocFunction::operator==(const DocFunction& other) const
{
    return IsConst == other.IsConst && Type == other.Type && Name == other.Name && VarParams == other.VarParams;
}

bool dp::DocFunction::IsEmpty() const
{
    return Type.empty() && Name.empty() && VarParams.empty();
}

std::string dp::DocFunction::ToString() const
{
    std::string isConstStr = (IsConst ? "const " : "");
    return isConstStr + Type + " " + Name + "(" + VarParams + ")";
}
