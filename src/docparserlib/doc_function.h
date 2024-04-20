#pragma once

#ifndef DOCFUNCTION_H
#define DOCFUNCTION_H

#include <string>

namespace dp {
    struct DocFunction {
        bool isConst;
        std::string Type;
        std::string Name;
        std::string VarParams;
    };
}

#endif // !DOCFUNCTION_H