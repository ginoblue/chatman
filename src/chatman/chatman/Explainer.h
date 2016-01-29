#pragma once
#include "Global.h"
class Explainer
{
public:
    Explainer(void);
    ~Explainer(void);
    int explain(wstring sentence);
    int combine_words(wstring sentence);
    int find_meaning(wstring word);
    int take_action(Object * subject, Object * action, Object * object);
    int find_method(Object * action);
};
