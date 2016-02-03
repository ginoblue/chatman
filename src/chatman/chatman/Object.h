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
    ObjMapMap attr_maps;
    friend wostream & operator <<(wostream & out,Object * & obj);
    bool include(Object * & obj);
};
class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();
    Object * find(const wstring & name, int & ret);
    ObjMap pool;

};