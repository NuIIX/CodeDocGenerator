#include "c_code_parser.h"
#include "file_utils.h"

/// @brief Конструктор
/// @param cPathStr Ссылка на строку, содержащую путь до файла с кодом
dp::CCodeParser::CCodeParser(const std::string& cPathStr) : _cPath{cPathStr}
{
}

/// @brief Конструктор
/// @param cPath Массив символов, содержащий путь до файла с кодом
dp::CCodeParser::CCodeParser(const char* cPath) : _cPath{std::string(cPath)}
{
}

/// @brief Конструктор
dp::CCodeParser::CCodeParser()
{
}

/// @brief Удаление лишних пробелов
/// @param str Ссылка на строку, в которой нужно удалить лишние пробелы
void dp::CCodeParser::RemoveSpaces(std::string& str)
{
    std::regex_replace(str, std::regex("\\s+"), " ");
    size_t firstNonSpace = str.find_first_not_of(' ');

    if (firstNonSpace != std::string::npos) {
        str = str.substr(firstNonSpace);
    }
}

/// @brief Установка пути в строковом представлении до файла с кодом
/// @param cPathStr Ссылка на строку, содержащую путь
void dp::CCodeParser::SetPath(const std::string& cPathStr)
{
    _cPath = cPathStr;
}

/// @brief Установка пути в символьном представлении до файла с кодом
/// @param cPath Массив символов, содержащий путь
void dp::CCodeParser::SetPath(const char* cPath)
{
    _cPath = std::string(cPath);
}

/// @brief Получение пути
/// @return const std::string& Путь до файла с кодом
const std::string& dp::CCodeParser::GetPath() const
{
    return _cPath;
}

/// @brief Получение документации
/// @return const std::vector<dp::DocUnit>& Документации
const std::vector<dp::DocUnit>& dp::CCodeParser::GetDocs() const
{
    return _docData;
}

/// @brief Получение регулярного выражения комментария
/// @return const std::regex& Регулярное выражение комментария
const std::regex& dp::CCodeParser::GetCommentPattern() const
{
    return _commentPattern;
}

/// @brief Получение регулярного выражения краткого описания
/// @return const std::regex& Регулярное выражение краткого описания
const std::regex& dp::CCodeParser::GetBriefPattern() const
{
    return _briefPattern;
}

/// @brief Получение регулярного выражения параметра
/// @return const std::regex& Регулярное выражение параметра
const std::regex& dp::CCodeParser::GetParamPattern() const
{
    return _paramPattern;
}

/// @brief Получение регулярного выражения возвращаемого значения
/// @return const std::regex& Регулярное выражение возвращаемого значения
const std::regex& dp::CCodeParser::GetReturnPattern() const
{
    return _returnPattern;
}

/// @brief Получение регулярного выражения заметки
/// @return const std::regex& Регулярное выражение заметки
const std::regex& dp::CCodeParser::GetNotePattern() const
{
    return _notePattern;
}

/// @brief Получение регулярного выражения исключения
/// @return const std::regex& Регулярное выражение исключения
const std::regex& dp::CCodeParser::GetThrowPattern() const
{
    return _throwPattern;
}

/// @brief Получение регулярного выражения функции
/// @return const std::regex& Регулярное выражение функции
const std::regex& dp::CCodeParser::GetFunctionPattern() const
{
    return _functionPattern;
}

/// @brief Парсинг документации
void dp::CCodeParser::Parse()
{
    std::ifstream file = OpenFileRead(_cPath);
    std::string line;
    std::smatch fMatches, bMatches, cMatches, pMatches, rMatches, nMatches, tMatches;
    DocUnit currentDocUnit;

    while (getline(file, line)) {
        if (std::regex_search(line, fMatches, _functionPattern)) {
            DocFunction function{
                    fMatches[1].length() != 0,
                    fMatches[2].str() + " " + fMatches[3].str() + " " + fMatches[4].str() + " " + fMatches[5].str(),
                    fMatches[6].str(),
                    fMatches[7].str()};

            RemoveSpaces(function.Type);
            currentDocUnit.Function = function;
            _docData.push_back(currentDocUnit);
            currentDocUnit = DocUnit();
        } else if (std::regex_search(line, cMatches, _commentPattern)) {
            std::string comment = cMatches[1].str();
            if (std::regex_search(comment, bMatches, _briefPattern)) {
                currentDocUnit.Brief = bMatches[1].str();
            } else if (std::regex_search(comment, pMatches, _paramPattern)) {
                DocParam param{pMatches[1].str(), pMatches[2].str()};
                currentDocUnit.Params.push_back(param);
            } else if (std::regex_search(comment, rMatches, _returnPattern)) {
                currentDocUnit.Return = rMatches[1].str();
            } else if (std::regex_search(comment, nMatches, _notePattern)) {
                currentDocUnit.Notes.push_back(nMatches[1].str());
            } else if (std::regex_search(comment, tMatches, _throwPattern)) {
                currentDocUnit.Throws.push_back(tMatches[1].str());
            }
        }
    }

    file.close();
}

/// @brief Вывод документации
/// @param stream Поток вывода
/// @param listDecorator Маркер списка
void dp::CCodeParser::PrintDocs(std::ostream& stream, const std::string& listDecorator)
{
    for (const auto& docUnit : _docData) {
        stream << "Function: "
               << "[" << (docUnit.Function.isConst ? "const" : "not const") << "] [" << docUnit.Function.Type << "] ["
               << docUnit.Function.Name << "] [" << docUnit.Function.VarParams << "]" << std::endl;

        stream << (docUnit.Brief.length() != 0 ? "Brief: " + docUnit.Brief + "\n" : "");

        stream << (docUnit.Return.length() != 0 ? "Return: " + docUnit.Return + "\n" : "");

        if (!docUnit.Params.empty()) {
            stream << "Params: " << std::endl;

            for (const auto& param : docUnit.Params) {
                stream << listDecorator << param.Name << ": " << param.Description << std::endl;
            }
        }

        if (!docUnit.Notes.empty()) {
            stream << "Notes: " << std::endl;

            for (const auto& note : docUnit.Notes) {
                stream << listDecorator << note << std::endl;
            }
        }

        if (!docUnit.Throws.empty()) {
            stream << "Throws: " << std::endl;

            for (const auto& throwStr : docUnit.Throws) {
                stream << listDecorator << throwStr << std::endl;
            }
        }

        stream << std::endl;
    }
}
