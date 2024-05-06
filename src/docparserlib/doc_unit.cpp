#include "doc_unit.h"

/// @brief Конструктор
dp::DocUnit::DocUnit()
{
}

/// @brief Конструктор
/// @param brief Описание
/// @param returnStr Возврат
/// @param notes Заметки
/// @param params Параметры
/// @param throws Исключения
/// @param function Функция
dp::DocUnit::DocUnit(
        const std::string& brief,
        const std::string& returnStr,
        const std::vector<std::string>& notes,
        const std::vector<dp::DocParam>& params,
        const std::vector<std::string>& throws,
        const dp::DocFunction& function)
    : Brief(brief), Return(returnStr), Notes(notes), Params(params), Throws(throws), Function(function)
{
}

bool dp::DocUnit::operator==(const DocUnit& other) const
{
    return Brief == other.Brief && Return == other.Return && Function == other.Function
            && std::equal(Notes.begin(), Notes.end(), other.Notes.begin())
            && std::equal(Params.begin(), Params.end(), other.Params.begin())
            && std::equal(Throws.begin(), Throws.end(), other.Throws.begin());
}

/// @brief Проверка на пустоту
/// @return true, если все поля в документе пусты
bool dp::DocUnit::IsEmpty() const
{
    return Brief.empty() && Return.empty() && Notes.empty() && Params.empty() && Throws.empty() && Function.IsEmpty();
}

/// @brief Конвертация
/// @param decorator Маркер списка
/// @return std::string Строка с документацией
std::string dp::DocUnit::ToString(const std::string& decorator) const
{
    std::string docUnitStr;

    docUnitStr.append("Function: " + Function.ToString() + "\n");

    docUnitStr.append(Brief.empty() ? "" : "Brief: " + Brief + "\n");
    docUnitStr.append(Return.empty() ? "" : "Return: " + Return + "\n");

    if (!Params.empty()) {
        docUnitStr.append("Params:\n");

        for (const auto& param : Params) {
            docUnitStr.append(decorator + param.ToString() + "\n");
        }
    }

    if (!Notes.empty()) {
        docUnitStr.append("Notes:\n");

        for (const auto& note : Notes) {
            docUnitStr.append(decorator + note + "\n");
        }
    }

    if (!Throws.empty()) {
        docUnitStr.append("Throws:\n");

        for (const auto& throwStr : Throws) {
            docUnitStr.append(decorator + throwStr + "\n");
        }
    }

    return docUnitStr;
}
