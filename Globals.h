//
// Created by izeren on 5/15/17.
//
#pragma once
#include <string>
#include <memory>
#include <map>

#include <vector>
#include <cstddef>
#include "TypeInfo.h"

namespace GL {
    class Globals {
    public:
        static int CLASS_COUNTER;
        static const std::ptrdiff_t DUMMY_POINTER;
        static std::map<std::string, std::shared_ptr<__TypeInfo>> registeredClasses;
        static std::map<std::ptrdiff_t, std::shared_ptr<__TypeInfo>> registeredPointers;
        static std::ptrdiff_t temp;
        static const std::shared_ptr<__TypeInfo> NULL_INFO;
    };
};