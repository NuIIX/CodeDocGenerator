#pragma once

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>
#include <string>

namespace dp {
    std::ifstream OpenFileRead(const std::string&);
}

#endif // !FILEUTILS_H
