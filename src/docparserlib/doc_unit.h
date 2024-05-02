#pragma once

#ifndef DOCUNIT_H
#define DOCUNIT_H

#include "doc_function.h"
#include "doc_param.h"
#include <string>
#include <vector>

namespace dp {
    struct DocUnit {
        std::string Return;
        std::vector<std::string> Notes;
        std::vector<dp::DocParam> Params;
        std::vector<std::string> Throws;
        dp::DocFunction Function;
    };
}

#endif // !DOCUNIT_H
