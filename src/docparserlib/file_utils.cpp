#include "file_utils.h"

/// @brief Чтение файла
/// @param path Путь к файлу
/// @return std::ifstream Поток на чтение файла
/// @throw std::invalid_argument Если файл нельзя открыть
std::ifstream dp::OpenFileRead(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to read file <" + path + ">");
    }

    return file;
}
