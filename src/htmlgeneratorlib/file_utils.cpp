#include "file_utils.h"

std::ofstream dp::OpenFileWrite(const std::string& path) {
    std::ofstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("Unable to write file <" + path + ">");
    }

    return file;
}