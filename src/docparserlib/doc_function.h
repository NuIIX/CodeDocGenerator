#pragma once

#ifndef DOCFUNCTION_H
#define DOCFUNCTION_H

#include <string>

namespace dp {
    /// @brief Информация о функции
    struct DocFunction {
        bool IsConst = false;
        std::string Type;
        std::string Name;
        std::string VarParams;

        DocFunction();
        DocFunction(bool, const std::string&, const std::string&, const std::string&);
        bool operator==(const DocFunction&) const;
        bool IsEmpty() const;
        std::string ToString() const;
    };
}

#endif // !DOCFUNCTION_H
