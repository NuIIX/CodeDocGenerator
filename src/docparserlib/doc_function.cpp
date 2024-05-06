#include "doc_function.h"

/// @brief Конструктор
dp::DocFunction::DocFunction()
{
}

/// @brief Конструктор
/// @param isConst Константа или нет
/// @param type Тип возвращаемого значения
/// @param name Наименование
/// @param params Все параметры в одну строку с типами
dp::DocFunction::DocFunction(bool isConst, const std::string& type, const std::string& name, const std::string& params)
    : IsConst(isConst), Type(type), Name(name), VarParams(params)
{
}

bool dp::DocFunction::operator==(const DocFunction& other) const
{
    return IsConst == other.IsConst && Type == other.Type && Name == other.Name && VarParams == other.VarParams;
}

/// @brief Проверка на пустоту
/// @return true, Если все поля функции пустые
bool dp::DocFunction::IsEmpty() const
{
    return Type.empty() && Name.empty() && VarParams.empty();
}

/// @brief Конвертация в строку
/// @return std::string Строка с функцией в формате [const type name(params...)]
std::string dp::DocFunction::ToString() const
{
    std::string isConstStr = (IsConst ? "const " : "");
    return isConstStr + Type + " " + Name + "(" + VarParams + ")";
}
