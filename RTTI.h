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


std::ptrdiff_t __GetDiffBetweenClasses( const std::string &childName, const std::string &parentName );

bool __WhetherChildIsParent( const std::string &childName, const std::string &parentName );


template<typename TO, typename FROM>
TO *__DynamicCast( FROM *f, const std::string &nameTo, const std::string &nameFrom ) {
    bool whetherClassInherited = __WhetherChildIsParent( nameTo, nameFrom );
    bool whetherActualClassInherited = __WhetherChildIsParent( Globals::registeredPointers.at(
            reinterpret_cast<std::ptrdiff_t>(f))->getName( ), nameTo );
    if ( whetherClassInherited && whetherActualClassInherited ) {
        auto diff = __GetDiffBetweenClasses( nameTo, nameFrom );
        auto result = reinterpret_cast<TO *>(reinterpret_cast<std::ptrdiff_t>(f) - diff);
        GL::Globals::registeredPointers[ reinterpret_cast<std::ptrdiff_t>(result) ] = Globals::registeredPointers.at(
                reinterpret_cast<std::ptrdiff_t>(f));
        return result;
    } else {
        return nullptr;
    }
};

#define TYPEID( T ) (*__Register::GetInfoOfClass(reinterpret_cast<std::ptrdiff_t>(T)))

#define DERIVED( CHILD, PARENT ) GL::Globals::registeredClasses.at(#CHILD)->\
AddParentInfo(#PARENT, GL::Globals::registeredClasses.at(#PARENT), __GetParentOffset<CHILD, PARENT>())

#define DECLARE_CLASS( T ) __Register __register##T (#T);

#define NEW_RTTI( POINTER_TYPE, T, ... ) reinterpret_cast<POINTER_TYPE *>(GL::Globals::temp = \
reinterpret_cast<std::ptrdiff_t>(reinterpret_cast<POINTER_TYPE *>(new T(__VA_ARGS__))));\
GL::Globals::registeredPointers[GL::Globals::temp] = GL::Globals::registeredClasses.at(#T)

#define DYNAMIC_CAST( FROM, TO, pointer ) __DynamicCast<TO, FROM>(pointer, #TO, #FROM)

#define EQUALS( LEFT, RIGHT ) (TYPEID(LEFT) == TYPEID(RIGHT))