#include "StdAfx.h"
#include "Database.h"
#include "Object.h"
#include "json/json.h"
extern Global * global;

Database::Database(void)
{
    json_name = "c:\\record.json";
}

Database::~Database(void)
{
    close();
}
int Database::open()
{
    int ret = open_json();
    return ret;
    
}
int Database::close()
{
    flush();
    close_json();
    return 0;
}
int Database::load()
{
    if (open() != 0)
        return -1;
    Json::Reader reader;
    Json::Value val;
    if (!reader.parse(file, val, false)){
        ERR("Json reader parse error, maybe empty file\n");
        return -1;
    }
    try {
        Json::Value::Members member = val.getMemberNames();
        Json::Value::Members::iterator it = member.begin();
        for (; it != member.end(); it++){
            if (load_obj(string_to_wstring(*it)) == NULL)
                ERR("Load object error\n");
        }
    }
    catch (Json::LogicError & e) {
    	cout << e.what() << endl;
        ERR("json file data not correct\n");
        close_json();
        return -1;
    }
    
    root = val;
    return 0;
}
string Database::wstring_to_string(const wstring & ws)
{
    const wchar_t * source = ws.c_str();
    size_t size = 2 * ws.size() + 1;
    char * dest = new char[size];
    memset(dest, 0, size);
    wcstombs(dest, source, size);
    std::string result = dest;
    delete [] dest;
    return result;
}
wstring Database::string_to_wstring(const string & s)  
{  
    const char * source = s.c_str();  
    size_t size = s.size() + 1;  
    wchar_t * dest = new wchar_t[size];  
    wmemset(dest, 0, size);  
    mbstowcs(dest, source, size);  
    std::wstring result = dest;  
    delete [] dest;   
    return result;  
}

Object * Database::find(const wstring & name, int & ret)
{
    Object * obj = global->obj_mgr->find(name, ret); 
    if (ret == CM_NOT_FOUND){
        if (is_existent_in_json(name)){
            obj = load_obj(name);
            ret = 0;
        }
    }
    return obj;
        
}
Object * Database::find(const wchar_t * name, int & ret)
{
    return find(wstring(name), ret);
}
Object * Database::find(const string & name, int & ret)
{
    return find(string_to_wstring(name), ret);
}
int Database::flush()
{
    // load() make pointer point to file's end
    // when fstream pointer point to file's end, it can
    // not return to beginning
    // work around to reopen : 
    close_json();
    Json::FastWriter writer;
    int ret = open();
    if (ret != 0)
        return ret;
    file << writer.write(root);
    return 0;
}
Object * Database::load_obj(const wstring & name)
{

    int ret = 0;
    Object * obj = global->obj_mgr->find(name, ret);
    if (obj != NULL)
        return obj;
    if (root[wstring_to_string(name)].isNull())
        return NULL;
    obj = new Object();
    string key = wstring_to_string(obj->name);
    obj->name = name;
    ObjMapMap::iterator it = obj->attr_maps.begin();
    for (; it != obj->attr_maps.end(); it++){
        ObjMap * map = it->second;
        string map_name = it->first;
        Json::Value attr = root[key][map_name];
        int size = attr.size();
        for (int i = 0; i < size; i++){
            Object * other = find(attr[i].asString(), ret);
            if (other == NULL){
                ERR("find object error\n");
                continue;
            }
            map->insert(ObjMap::value_type(other->name, other));
        }
    }
    
    return obj;
}
int Database::save_obj(Object * & obj)
{
    
    string key = wstring_to_string(obj->name);
    Json::Value attrs;
    ObjMapMap::iterator it = obj->attr_maps.begin();
    for (; it != obj->attr_maps.end(); it++){
        ObjMap * map = it->second;
        string map_name = it->first;
        ObjMap::iterator i = map->begin();
        for (; i != map->end(); i++){
            attrs[map_name].append(wstring_to_string(i->first));
        }
        
    }   
    root[key] = attrs;
    return 0;
}
int Database::open_json()
{
    if (!file.is_open()){
        //create file
        ofstream of(json_name.c_str(), ios::app);
        if (of.is_open())
            of.close();
        file.open(json_name.c_str(), ios::in |
            ios::out | ios::binary);
        if (!file.is_open()){
            ERR("Database open file error\n");
            return -1;
        }
    }
    return 0;
}
int Database::close_json()
{
    if (file.is_open())
        file.close();
    return 0;
}
int Database::save_all_objs()
{
    int ret = 0;
    ObjMap::iterator it = global->obj_mgr->pool.begin();
    for (; it != global->obj_mgr->pool.end(); it++) {
        ret = save_obj(it->second);
        if (ret != 0){
            ERR("save obj error\n");
            return ret;
        }
    }
    return ret;
}
bool Database::is_existent_in_json(const wstring & name)
{
    int ret = open_json();
    if (ret != 0)
        return false;
    return !root[wstring_to_string(name)].isNull();
}