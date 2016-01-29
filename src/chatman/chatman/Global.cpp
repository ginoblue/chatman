#include "StdAfx.h"
#include "Global.h"
#include "Object.h"
#include "Database.h"
Global * global = NULL;
Global::Global()
{
    obj_mgr = new ObjectManager();
    db = new Database();
}

Global::~Global()
{
    if (obj_mgr)
        delete obj_mgr;
    if (db)
        delete db;
}
Global * Global::get_instance(void)
{
    if (global == NULL)
        global = new Global();
    return global;
}
