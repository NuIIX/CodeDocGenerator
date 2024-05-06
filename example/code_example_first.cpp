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

/// @brief Проверка на чётность
/// @param num Число для проверки
/// @return bool Возвращает true, если число чётное, иначе false
bool isEven(int num) {
    return num % 2 == 0;
}

/// @brief Поиск максимального элемента в векторе
/// @param vec Вектор для поиска
/// @return int Максимальный элемент вектора
/// @throw std::invalid_argument Если вектор пуст
int findMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    return *max_element(vec.begin(), vec.end());
}