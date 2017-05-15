//
// Created by izeren on 5/15/17.
//

#include "RTTI.h"
#include "TypeInfo.h"
#include <iostream>


__Register::__Register( const char *name) {
    if ( registeredClasses.find( name ) == registeredClasses.end( )) {
        auto infoPtr = std::make_shared<__TypeInfo>(name, CLASS_COUNTER++);
        registeredClasses[name] = infoPtr;
    }
}

const std::shared_ptr<__TypeInfo> __Register::GetInfoOfClass( const std::string &name ) {
    if ( registeredClasses.find( name ) != registeredClasses.end( )) {
        return registeredClasses.at( name );
    } else {
        return nullptr;
    }
}

std::pair<bool, std::ptrdiff_t> __CheckHierarchy( const std::string &childName, const std::string &parentName ) {
    bool isInherited = false;
    std::ptrdiff_t diff = 0;
    auto parentInfos = __Register::GetInfoOfClass( childName )->getParentInfos( );
    int numOfParents = static_cast<int>(parentInfos.size( ));
    if ( numOfParents ) {
        for ( auto parentInfo : parentInfos ) {
            if ( parentInfo.first == parentName ) {
                isInherited = true;
                diff += parentInfo.second->offset;
                return std::make_pair(isInherited, diff);
            } else {
                auto result = __CheckHierarchy( parentInfo.first, parentName );
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