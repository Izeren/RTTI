//
// Created by izeren on 5/15/17.
//
#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include "Globals.h"
#include "TypeInfo.h"

using namespace GL;

template<typename Child, typename Parent>
std::ptrdiff_t __GetParentOffset( ) {
    return reinterpret_cast<std::ptrdiff_t>(static_cast<Parent *>(
                                                    reinterpret_cast<Child *>(Globals::DUMMY_POINTER))
                                            ) - Globals::DUMMY_POINTER;
};

class __Register {
public:
    __Register( const char *name );

    static const std::shared_ptr<__TypeInfo> GetInfoOfClass( std::ptrdiff_t pointer );
};


std::pair<bool, std::ptrdiff_t> __CheckClassHierarchy( const std::string &childName, const std::string &parentName );

bool __CheckActualHierarchy( const std::string &childName, std::ptrdiff_t parentPointer );


template<typename TO, typename FROM>
TO *__DynamicCast( FROM *f, const std::string &nameTo, const std::string &nameFrom ) {
    auto classHierarchyInfo = __CheckClassHierarchy( nameTo, nameFrom );
    bool actualHierarchyInfo = __CheckActualHierarchy( nameTo, reinterpret_cast<std::ptrdiff_t>(f));
    if ( classHierarchyInfo.first && actualHierarchyInfo ) {
        return reinterpret_cast<TO *>(reinterpret_cast<std::ptrdiff_t>(f) - classHierarchyInfo.second);
    } else {
        return nullptr;
    }
};

#define TYPEID( T ) (*__Register::GetInfoOfClass(reinterpret_cast<std::ptrdiff_t>(T)))
#define DERIVED(CHILD, PARENT) GL::Globals::registeredClasses.at(#CHILD)->\
AddParentInfo(#PARENT, GL::Globals::registeredClasses.at(#PARENT), __GetParentOffset<CHILD, PARENT>())
#define DECLARE_CLASS( T ) __Register __register##T (#T);
#define NEW_RTTI(T, ...) reinterpret_cast<T *>(GL::Globals::temp = \
reinterpret_cast<std::ptrdiff_t>(new T(__VA_ARGS__)));\
GL:Globals::registeredPointers[GL::Globals::temp] = GL::Globals::registeredClasses.at(#T);
#define DYNAMIC_CAST(FROM, TO, pointer) __DynamicCast<TO, FROM>(pointer, #TO, #FROM)