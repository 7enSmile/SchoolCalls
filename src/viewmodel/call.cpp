#include "../../include/viewmodel/call.h"

Call::Call(int h, int m, int t, QString p)
{
    hours = h;
    minuts = m;
    type = t;
    soundPatch = p;
}

Call::Call()
{

}
