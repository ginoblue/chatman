#include "StdAfx.h"
#include "Global.h"
#include "Object.h"
#include "Database.h"
#include "Explainer.h"
Global * global = NULL;
Global::Global()
{
    obj_mgr = new ObjectManager();
    db = new Database();
    explainer = new Explainer();
}

Global::~Global()
{
    if (obj_mgr)
        delete obj_mgr;
    if (db)
        delete db;
    if (explainer)
        delete explainer;
}
Global * Global::get_instance(void)
{
    if (global == NULL)
        global = new Global();
    return global;
}
