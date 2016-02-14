#pragma once
#include <fstream>
#include "json/json.h"
#include "Global.h"
class Database
{
public:
    Database(void);
    ~Database(void);
    int open();
    int flush();
    int load();
    int close();
    Object * find(const string & name, int & ret);
    Object * find(const wstring & name, int & ret);
    Object * find(const wchar_t * name, int & ret);
    int save_obj(Object * & obj);
    int save_all_objs();
private:
    int open_json();
    int close_json();
    string wstring_to_string(const wstring & ws);
    wstring string_to_wstring(const string & s);
    bool is_existent_in_json(const wstring & name);
    Object * Database::load_obj(const wstring & name);
    //for read
    ifstream file_in;
    //for write
    ofstream file_out;
    Json::Value root;
    string json_name;
    string tmp_json_name;
};
