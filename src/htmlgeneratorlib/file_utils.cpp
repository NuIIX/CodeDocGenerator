#include "file_utils.h"

/// @brief Запись файла
/// @param path Путь к файлу
/// @return std::ofstream Поток на запись в файл
/// @throw std::invalid_argument Если файл нельзя открыть
std::ofstream hg::OpenFileWrite(const std::string& path)
{
    std::ofstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to write file <" + path + ">");
    }

    return file;
}

/// @brief Чтение файла
/// @param path Путь к файлу
/// @return std::ifstream Поток на чтение файла
/// @throw std::invalid_argument Если файл нельзя открыть
std::ifstream hg::OpenFileRead(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to read file <" + path + ">");
    }

    return file;
}
