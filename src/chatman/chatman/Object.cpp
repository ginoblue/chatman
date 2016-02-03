#include "StdAfx.h"
#include "Object.h"
#include "Global.h"
extern Global * global;

Object::Object(wstring name){
    this->name = name;
    this->attr_maps["inclusions"] = &(this->inclusions);
    this->attr_maps["equivalences"] = &(this->equivalences);
    this->attr_maps["determiners"] = &(this->determiners);
    global->obj_mgr->pool.insert(ObjMap::value_type(name, this));
}
Object::~Object(void)
{
}
bool Object::include(Object * & obj){
    return (inclusions.find(obj->name) != inclusions.end());
}
wostream & operator <<(wostream & out, Object * & obj)
{
    wcout << obj->name <<endl;
    ObjMapMap::iterator it = obj->attr_maps.begin();
    for (; it != obj->attr_maps.end(); it++){
        cout << it->first << ":" << endl;
        ObjMap map = *(it->second);
        ObjMap::iterator i = map.begin();
        for (; i != map.end(); i++){
            wcout << i->first << " ";
        }
        cout << endl;
    }
    return out;
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
Object * ObjectManager::find(const wstring & name, int & ret)
{
    Object * obj = NULL;
    ObjMap::iterator it = pool.find(name);
    if (it != pool.end()){
        obj = it->second;
        return 0;
    }
    ret = CM_NOT_FOUND;
    return obj;
}