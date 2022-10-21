#include "../../include/viewmodel/call.h"



Call::Call(int h, int m, int t, QString p, int s, int sp)
{
    hours = h;
    minutes = m;
    type = t;
    soundPatch = p;
    saturday = s;
    special = sp;

}

Call::Call()
{

}
