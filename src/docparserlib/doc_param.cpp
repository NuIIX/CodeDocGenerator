#include "doc_param.h"

/// @brief Конструктор
dp::DocParam::DocParam()
{
}

/// @brief Констуруктор
/// @param name Наименование
/// @param description Описание
dp::DocParam::DocParam(const std::string& name, const std::string& description) : Name(name), Description(description)
{
}

bool dp::DocParam::operator==(const DocParam& other) const
{
    return Name == other.Name && Description == other.Description;
}

/// @brief Конвертация в строку
/// @return std::string Строка с параметром в виде [name: description]
std::string dp::DocParam::ToString() const
{
    return Name + ": " + Description;
}
