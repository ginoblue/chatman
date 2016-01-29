#include "StdAfx.h"
#include "Object.h"
#include "Global.h"
extern Global * global;

Object::Object(wstring name){
    this->name = name;
    global->obj_mgr->pool.insert(ObjMap::value_type(name, this));
}
Object::~Object(void)
{
}
bool Object::include(Object & obj){
    return (inclusions.find(obj.name) != inclusions.end());
}
ObjectManager::ObjectManager()
{
}
ObjectManager::~ObjectManager(){
    ObjMap::iterator it = pool.begin();
    for (; it != pool.end(); it++)
        if (it->second)
            delete it->second;
}