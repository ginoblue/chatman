#pragma once
#include "Global.h"

class Object
{
public:
    Object(wstring name = L"");
    virtual ~Object();
    wstring name;
    ObjMap inclusions;
    ObjMap equivalences;
    ObjMap determiners;
    bool include(Object & obj);
};
class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();
    ObjMap pool;

};