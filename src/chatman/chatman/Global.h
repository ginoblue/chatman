#pragma once
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include "thread.h"
#include <stdio.h>
using namespace std;
class Object;
class ObjectManager;
class Database;
class Explainer;
typedef unsigned int uint32;
typedef map<wstring, Object *> ObjMap;
typedef map<string, ObjMap *> ObjMapMap;
typedef int int32;
typedef long long int int64;
typedef long long unsigned int uint64;

#define ERR(fmt, ...) printf("%s:%d - " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define CM_NOT_FOUND 1
class Global
{
public:
    Database * db;
    Explainer * explainer;
    ObjectManager * obj_mgr;
    static Global * get_instance();
    ~Global();
private:
    Global();
    
    
    

};

