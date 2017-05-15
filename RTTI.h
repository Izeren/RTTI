//
// Created by izeren on 5/15/17.
//
#pragma once
#include <cstddef>
#include <functional>
#include <memory>
#include "Globals.h"


template<typename Child, typename Parent>
std::ptrdiff_t __GetParentOffset( ) {
    return reinterpret_cast<std::ptrdiff_t>(static_cast<Parent *>(DUMMY_POINTER)) -
           reinterpret_cast<std::ptrdiff_t>(static_cast<Child *>(DUMMY_POINTER));
};

class __Register {
public:
    __Register( const char *name);

    static const std::shared_ptr<__TypeInfo> GetInfoOfClass( const std::string &name );
};


std::pair<bool, std::ptrdiff_t> __CheckHierarchy(const std::string &childName, const std::string &parentName);


template<typename TO, typename FROM>
TO* __DynamicCast( FROM *f, const std::string &nameTo, const std::string &nameFrom ) {
    auto hierarchyInfo = __CheckHierarchy( nameTo, nameFrom );
    if ( hierarchyInfo.first ) {
        return reinterpret_cast<TO *>(reinterpret_cast<std::ptrdiff_t>(f) - hierarchyInfo.second);
    } else {
        return nullptr;
    }
};

#define TYPEID(T) (*__Register::GetInfoOfClass(std::string(#T)))
#define DECLARE_CLASS(T) __Register __register##T (#T);