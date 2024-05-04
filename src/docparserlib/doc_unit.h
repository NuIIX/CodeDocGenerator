#pragma once

#ifndef DOCUNIT_H
#define DOCUNIT_H

#include "doc_function.h"
#include "doc_param.h"
#include <string>
#include <vector>

namespace dp {
    /// @brief Единица документации
    struct DocUnit {
        std::string Brief;
        std::string Return;
        std::vector<std::string> Notes;
        std::vector<dp::DocParam> Params;
        std::vector<std::string> Throws;
        dp::DocFunction Function;

        bool operator==(const DocUnit& other) const
        {
            return Brief == other.Brief && Return == other.Return && Function == other.Function
                    && std::equal(Notes.begin(), Notes.end(), other.Notes.begin())
                    && std::equal(Params.begin(), Params.end(), other.Params.begin())
                    && std::equal(Throws.begin(), Throws.end(), other.Throws.begin());
        }
    };
}

#endif // !DOCUNIT_H
