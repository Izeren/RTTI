//
// Created by izeren on 5/15/17.
//

#include <string>
#include <memory>
#include <map>
#include <vector>

class __TypeInfo;

int CLASS_COUNTER = 0;

std::map<std::string, std::shared_ptr<__TypeInfo>> registeredClasses = {};

const std::ptrdiff_t DUMMY_POINTER = 0;

std::vector<int> globalTest = {};