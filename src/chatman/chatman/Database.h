#pragma once
#include <fstream>
class Database
{
public:
    Database(void);
    ~Database(void);
    int open();
    fstream file;
    Json::Value root;
    int get_object(Object * obj);
};
