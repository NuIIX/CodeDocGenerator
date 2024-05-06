/// @brief Конвертация списка в html представление
/// @param name Заголовок списка
/// @param listItems Элементы списка
/// @return std::string html шаблон в строковом представлении со списком
std::string hg::TemplateProcessor::ConvertListToHtml(const std::string& name, const std::vector<std::string>& listItems)
{
    if (listItems.empty()) {
        return "";
    }

    if (listItems.at(0) == "") {
        return "";
    }

    std::string htmlListStr = "<h2>" + name + "</h2>\n";

    for (const auto& item : listItems) {
        htmlListStr.append("<p>").append(item).append("</p>\n");
    }

    return htmlListStr;
}

/// @brief Сортировка вектора по возрастанию
/// @param vec Вектор для сортировки
/// @return std::vector<int> Отсортированный вектор
std::vector<int> sortVector(const std::vector<int>& vec) {
    std::vector<int> sorted_vec = vec;
    sort(sorted_vec.begin(), sorted_vec.end());
    return sorted_vec;
}

/// @brief Подсчёт количества вхождений элемента в вектор
/// @param vec Вектор для поиска
/// @param element Элемент для подсчёта
/// @return int Количество вхождений элемента в вектор
int countElement(const std::vector<int>& vec, int element) {
    return count(vec.begin(), vec.end(), element);
}

/// @brief Перевод числа из десятичной системы в двоичную
/// @param num Число для перевода
/// @return std::string Число в двоичной системе
std::string decimalToBinary(int num) {
    std::string binary;
    while(num) {
        binary.insert(binary.begin(), '0' + num % 2);
        num /= 2;
    }
    return binary;
}