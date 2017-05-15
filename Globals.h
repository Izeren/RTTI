//
// Created by izeren on 5/15/17.
//
#pragma once
#include <string>
#include <memory>
#include <map>

#include <vector>

class __TypeInfo;

extern int CLASS_COUNTER;

extern std::map<std::string, std::shared_ptr<__TypeInfo>> registeredClasses;

extern const std::ptrdiff_t DUMMY_POINTER;

extern std::vector<int> globalTest;