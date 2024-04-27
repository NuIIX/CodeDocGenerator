#include "file_utils.h"

std::ifstream dp::OpenFileRead(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to read file <" + path + ">");
    }

    return file;
}