#include "StdAfx.h"
#include "Explainer.h"
#include "Database.h"
#include "Object.h"
extern Global * global;
Explainer::Explainer(void)
{
}

Explainer::~Explainer(void)
{
}
void Explainer::run()
{
    while (1){
        wstring sentence;
        wcin >> sentence;
        if (sentence == L"q" || sentence == L"Q")
            break;
        explain(sentence);
    }
    

}
int Explainer::combine_words(wstring sentence)
{
    //chat man inside explain func, add by learning
    int ret = 0;
    Object * explainer = global->db->find(L"__explain__", ret);
    //the default way to explain
    if (explainer == NULL){
        int size = sentence.length();
        int pos = 0;
        Object * obj = NULL;
        while(pos < size){
            int i = pos;
            int cnt = 1;
            for (; i < size && i + cnt <= size;){
                obj = find_meaning(sentence.substr(i, cnt));
                if (obj == NULL){
                    cnt++;
                    continue;
                }
                i += cnt;
                cnt = 1;
                wcout << obj;
            }
            pos = i + 1;
        }
    }else{
        ObjMap::iterator it = explainer->equivalences.begin();
        for (; it != explainer->equivalences.end(); it++){
            combine_words(it->second->name, sentence);
        }
    }
    
        
    return 0;
}
int Explainer::explain(wstring sentence){
    combine_words(sentence);
    return 0;
}
int Explainer::combine_words(wstring func, wstring sentence){
    return 0;
}
Object * Explainer::find_meaning(wstring word)
{
    int ret = 0;
    return global->db->find(word, ret);
}
int Explainer::take_action(Object * subject, Object * action, Object * object)
{
    return 0;
}
int Explainer::find_method(Object * action)
{
    return 0;
}
