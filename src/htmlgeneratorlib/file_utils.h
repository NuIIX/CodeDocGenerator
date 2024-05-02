#pragma once

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>
#include <string>

namespace hg {
    std::ofstream OpenFileWrite(const std::string&);
    std::ifstream OpenFileRead(const std::string&);
}

#endif // !FILEUTILS_H
