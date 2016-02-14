#include "StdAfx.h"
#include "Database.h"
#include "Object.h"
#include "json/json.h"
extern Global * global;

Database::Database(void)
{
    json_name = "c:\\record.json";
    tmp_json_name = json_name + ".tmp";
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
    remove(json_name.c_str());
    rename(tmp_json_name.c_str(), json_name.c_str());
    return 0;
}
int Database::load()
{
    if (open() != 0)
        return -1;
    Json::Reader reader;
    if (!reader.parse(file_in, root, false)){
        ERR("Json reader parse error, maybe empty file\n");
        root.clear();
        return -1;
    }
    try {
        Json::Value::Members member = root.getMemberNames();
        Json::Value::Members::iterator it = member.begin();
        for (; it != member.end(); it++){
            if (load_obj(string_to_wstring(*it)) == NULL)
                ERR("Load object error\n");
        }
    }
    catch (Json::LogicError & e) {
    	cout << e.what() << endl;
        ERR("Json file data not correct\n");
        close_json();
        return -1;
    }
    
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
    Json::FastWriter writer;
    file_out.open(tmp_json_name.c_str());
    if (!file_out.is_open()){
        ERR("Database open file error\n");
        return -1;
    }
    file_out << writer.write(root);
    file_out.close();
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
    
    obj->name = name;
    string key = wstring_to_string(name);
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
        attrs[map_name] = Json::nullValue;
        for (; i != map->end(); i++){
            attrs[map_name].append(wstring_to_string(i->first));
        }
        
    }
    root[key] = attrs;
    return 0;
}
int Database::open_json()
{
    if (!file_in.is_open()){
        file_in.open(json_name.c_str(), ios::app | ios::binary);
        if (!file_in.is_open()){
            ERR("Database open file error\n");
            return -1;
        }
    }
    return 0;
}
int Database::close_json()
{
    if (file_in.is_open())
        file_in.close();
    return 0;
}
int Database::save_all_objs()
{
    int ret = 0;
    ObjMap::iterator it = global->obj_mgr->pool.begin();
    for (; it != global->obj_mgr->pool.end(); it++) {
        ret = save_obj(it->second);
        if (ret != 0){
            ERR("save obj error, obj name: %s\n",
                wstring_to_string(it->second->name));
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