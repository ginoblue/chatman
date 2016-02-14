// chatman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Global.h"
#include "Object.h"
#include "Database.h"
extern Global * global;
int _tmain(int argc, _TCHAR* argv[])
{
    std::locale::global(std::locale(""));
    global = Global::get_instance();
    global->db->open();
    global->db->load();
    int ret = 0;
    /*
    Object * test1 = new Object(L"电脑");
    Object * test2 = new Object(L"显示器");
    Object * test3 = new Object(L"主机");
    Object * test4 = new Object(L"鼠标");
    Object * test5 = new Object(L"计算机");
    Object * test6 = new Object(L"小明");
    test1->inclusions.insert(ObjMap::value_type(test2->name, test2));
    test1->inclusions.insert(ObjMap::value_type(test3->name, test3));
    test1->inclusions.insert(ObjMap::value_type(test4->name, test4));
    test1->equivalences.insert(ObjMap::value_type(test5->name, test5));
    test1->determiners.insert(ObjMap::value_type(test6->name, test6));
    global->db->save_all_objs();
    
    
    Object * test = global->db->find(L"电脑", ret);
    wcout<<test;
    */
    getchar();
    if (global)
        delete global;
	return 0;
}

