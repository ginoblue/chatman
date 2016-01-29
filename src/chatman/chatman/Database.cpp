#include "StdAfx.h"
#include "Database.h"
#include "json/json.h"
Database::Database(void)
{
}

Database::~Database(void)
{
    close();
}
int Database::open()
{
    if (!file.is_open())
        file.open("record.json, ios::in | ios::out | ios::binary");
    if (!file.good()){
        ERR("Database open file error\n");
        return -1;
    }
    Json::Reader reader;
    return reader.parse(file, root, false) ? 0 : -1;
}
int Database::close()
{
    if (file.is_open())
        file.close();
    return 0;


}
int Database::get_object(Object * obj)
{

}