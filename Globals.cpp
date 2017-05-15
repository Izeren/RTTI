//
// Created by izeren on 5/15/17.
//

#include "Globals.h"

int GL::Globals::CLASS_COUNTER = 0;

const std::ptrdiff_t GL::Globals::DUMMY_POINTER = 0;

std::ptrdiff_t GL::Globals::temp = 0;

std::map<std::string, std::shared_ptr<__TypeInfo>> GL::Globals::registeredClasses = {};

std::map<std::ptrdiff_t, std::shared_ptr<__TypeInfo>> GL::Globals::registeredPointers = {};

const std::shared_ptr<__TypeInfo> GL::Globals::NULL_INFO = std::make_shared<__TypeInfo>("", -1);