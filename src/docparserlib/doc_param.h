#pragma once

#ifndef DOCPARAM_H
#define DOCPARAM_H

#include <string>

namespace dp {
    /// @brief Параметр функции
    struct DocParam {
        std::string Name;
        std::string Description;

        DocParam();
        DocParam(const std::string&, const std::string&);
        bool operator==(const DocParam&) const;
        std::string ToString() const;
    };
}

#endif // !DOCPARAM_H
