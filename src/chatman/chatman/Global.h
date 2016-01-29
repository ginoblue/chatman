#pragma once
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include "thread.h"
#include "stdio.h"
using namespace std;
class Object;
class ObjectManager;
class Database;
typedef unsigned int uint32;
typedef map<wstring, Object *> ObjMap;
typedef int int32;
typedef long long int int64;
typedef long long unsigned int uint64;
typedef int32 ssize_t;
typedef int64 off_t;
typedef int32 mode_t;
#define ERR(fmt, ...) pritnf("%s:%d - " fmt, __WHAT_FUNCTION__, __LINE__, ##__VA_ARGS__)
class Global
{
public:
    Database * db;
    ObjectManager * obj_mgr;
    static Global * get_instance();
private:
    Global();
    ~Global();
    
    

};

