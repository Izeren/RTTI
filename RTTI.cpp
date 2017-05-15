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
        return nullptr;
    }
}

std::pair<bool, std::ptrdiff_t> __CheckClassHierarchy( const std::string &childName, const std::string &parentName ) {
    bool isInherited = false;
    std::ptrdiff_t diff = 0;
    auto parentInfos = GL::Globals::registeredClasses.at(childName)->getParentInfos();
    int numOfParents = static_cast<int>(parentInfos.size( ));
    if ( numOfParents ) {
        for ( auto parentInfo : parentInfos ) {
            if ( parentInfo.first == parentName ) {
                isInherited = true;
                diff += parentInfo.second->offset;
                return std::make_pair(isInherited, diff);
            } else {
                auto result = __CheckClassHierarchy( parentInfo.first, parentName );
                isInherited = result.first || isInherited;
                if (isInherited) {
                    diff += result.second;
                    return std::make_pair(isInherited, diff);
                }
            }
        }
    }
    return std::make_pair(isInherited, diff);
}

bool __CheckActualHierarchy( const std::string &childName, std::ptrdiff_t parentPointer) {
    bool isInherited = false;
    auto parentInfos = GL::Globals::registeredClasses.at(childName)->getParentInfos();
    auto parentName = GL::Globals::registeredPointers.at(parentPointer)->getName();
    int numOfParents = static_cast<int>(parentInfos.size( ));
    if ( numOfParents ) {
        for ( auto parentInfo : parentInfos ) {
            if ( parentInfo.first == parentName ) {
                isInherited = true;
            } else {
                isInherited = isInherited || __CheckActualHierarchy( parentInfo.first, parentPointer );
            }
            if (isInherited) {
                return isInherited;
            }
        }
    }
    return isInherited;
}