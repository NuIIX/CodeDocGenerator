#pragma once

#ifndef DOCPARAM_H
#define DOCPARAM_H

#include <string>

namespace dp {
    /// @brief Параметр функции
    struct DocParam {
        std::string Name;
        std::string Description;

        bool operator==(const DocParam& other) const
        {
            return Name == other.Name && Description == other.Description;
        }
    };
}

#endif // !DOCPARAM_H
