#include "../../include/viewmodel/call.h"



Call::Call(int i, int h, int m, int t, QString p, int s)
{
    id = i;
    hours = h;
    minutes = m;
    type = t;
    soundPatch = p;
    saturday = s;

}

Call::Call()
{

}
