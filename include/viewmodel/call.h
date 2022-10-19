#ifndef CALL_H
#define CALL_H

#include <QString>



class Call
{
public:
    int id;
    int hours;
    int minuts;
    int type;
    QString soundPatch;
    Call(int, int, int, QString);
    Call();
};

#endif // CALL_H
