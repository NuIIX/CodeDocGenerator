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

        DocUnit();
        DocUnit(const std::string&,
                const std::string&,
                const std::vector<std::string>&,
                const std::vector<dp::DocParam>&,
                const std::vector<std::string>&,
                const dp::DocFunction&);
        bool operator==(const DocUnit&) const;
        bool IsEmpty() const;
        std::string ToString(const std::string& = "") const;
    };
}

#endif // !DOCUNIT_H
