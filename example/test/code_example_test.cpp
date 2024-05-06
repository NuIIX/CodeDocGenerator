/// @brief Запись файла
/// @param path Путь к файлу
/// @return std::ofstream Поток на запись в файл
/// @note Примечание
/// @throw std::invalid_argument Если файл нельзя открыть
std::ofstream hg::OpenFileWrite(const std::string& path)
{
    std::ofstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to write file <" + path + ">");
    }

    return file;
}