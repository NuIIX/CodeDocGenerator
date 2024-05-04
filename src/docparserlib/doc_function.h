#pragma once

#ifndef DOCFUNCTION_H
#define DOCFUNCTION_H

#include <string>

namespace dp {
    /// @brief Информация о функции
    struct DocFunction {
        bool isConst;
        std::string Type;
        std::string Name;
        std::string VarParams;

        bool operator==(const DocFunction& other) const
        {
            return isConst == other.isConst && Type == other.Type && Name == other.Name && VarParams == other.VarParams;
        }
    };
}

#endif // !DOCFUNCTION_H
