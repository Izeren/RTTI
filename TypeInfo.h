//
// Created by izeren on 5/15/17.
//
#pragma once

#include <string>
#include <map>
#include <memory>

using __Name = std::string;

class __TypeInfo;

struct __ParentInfo {
    std::shared_ptr<__TypeInfo> info;
    std::ptrdiff_t offset;
    __ParentInfo(const std::shared_ptr<__TypeInfo> &infoPtr, std::ptrdiff_t offset);
};
using __ParentInfoPtr = std::shared_ptr<__ParentInfo>;


class __TypeInfo {
public:
    __TypeInfo( std::string name, int hash );

    void AddParentInfo( const std::string &name, std::shared_ptr<__TypeInfo>, int offset );

    const std::string &getName( ) const;

    int getHash( ) const;

    const std::map<__Name, __ParentInfoPtr> &getParentInfos( ) const;

    std::string ToString() const;

private:
    std::string name;
    int hash;
    std::map<__Name, __ParentInfoPtr> parentInfos;

};

bool operator ==(const __TypeInfo &left, const __TypeInfo &right);

bool operator ==(int null, const __TypeInfo &right);

bool operator ==(const __TypeInfo &left, int null);
