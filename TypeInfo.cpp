//
// Created by izeren on 5/15/17.
//

#include "TypeInfo.h"
#include <vector>


__TypeInfo::__TypeInfo( std::string name, int hash ) :
        name( name ), hash( hash ) {
}

void __TypeInfo::AddParentInfo( const std::string &name, std::shared_ptr<__TypeInfo> parentTypeInfo, int offset ) {
    auto parentInfo = std::make_shared<__ParentInfo>( parentTypeInfo, offset );
    parentInfos[ name ] = parentInfo;
}

const std::string &__TypeInfo::getName( ) const {
    return name;
}

int __TypeInfo::getHash( ) const {
    return hash;
}

const std::map<__Name, __ParentInfoPtr> &__TypeInfo::getParentInfos( ) const {
    return parentInfos;
}

std::string __TypeInfo::ToString( ) const {
    std::string parentNames = "";
    for (auto parent : parentInfos) {
        parentNames += parent.first + " ";
    }
    return "Name: " + name + " Hash: " + std::to_string(hash) + " [ " + parentNames + "]\n";
}


__ParentInfo::__ParentInfo( const std::shared_ptr<__TypeInfo> &infoPtr, std::ptrdiff_t offset ) : info(infoPtr), offset(offset){
}

bool operator ==(const __TypeInfo &left, const __TypeInfo &right) {
    return left.getHash() == right.getHash();
}