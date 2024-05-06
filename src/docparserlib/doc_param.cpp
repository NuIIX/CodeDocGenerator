#include "doc_param.h"

dp::DocParam::DocParam()
{
}

dp::DocParam::DocParam(const std::string& name, const std::string& description) : Name(name), Description(description)
{
}

bool dp::DocParam::operator==(const DocParam& other) const
{
    return Name == other.Name && Description == other.Description;
}

std::string dp::DocParam::ToString() const
{
    return Name + ": " + Description;
}
