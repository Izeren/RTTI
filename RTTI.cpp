//
// Created by izeren on 5/15/17.
//

#include "RTTI.h"
#include <iostream>

__Register::__Register( const char *name) {
    if ( Globals::registeredClasses.find( name ) == Globals::registeredClasses.end( )) {
        auto infoPtr = std::make_shared<__TypeInfo>(name, Globals::CLASS_COUNTER++);
        Globals::registeredClasses[name] = infoPtr;
    }
}

const std::shared_ptr<__TypeInfo> __Register::GetInfoOfClass( std::ptrdiff_t pointer ) {
    if ( Globals::registeredPointers.find( pointer ) != Globals::registeredPointers.end( )) {
        return Globals::registeredPointers.at( pointer );
    } else {
        return Globals::NULL_INFO;
    }
}

std::ptrdiff_t __GetDiffBetweenClasses( const std::string &childName, const std::string &parentName ) {
    std::ptrdiff_t diff = 0;
    if (childName == parentName) {
        return diff;
    }
    auto parentInfos = GL::Globals::registeredClasses.at(childName)->getParentInfos();
    int numOfParents = static_cast<int>(parentInfos.size( ));
    if ( numOfParents ) {
        for ( auto parentInfo : parentInfos ) {
            if ( parentInfo.first == parentName ) {
                diff += parentInfo.second->offset;
                return diff;
            } else {
                diff += __GetDiffBetweenClasses( parentInfo.first, parentName );
            }
        }
    }
    return diff;
}

bool __WhetherChildIsParent( const std::string &childName, const std::string &parentName) {
    if (childName == parentName) {
        return true;
    }
    bool isInherited = false;
    auto parentInfos = GL::Globals::registeredClasses.at(childName)->getParentInfos();
    int numOfParents = static_cast<int>(parentInfos.size( ));
    if ( numOfParents ) {
        for ( auto parentInfo : parentInfos ) {
            if ( parentInfo.first == parentName ) {
                isInherited = true;
            } else {
                isInherited = isInherited || __WhetherChildIsParent( parentInfo.first, parentName );
            }
            if (isInherited) {
                return isInherited;
            }
        }
    }
    return isInherited;
}