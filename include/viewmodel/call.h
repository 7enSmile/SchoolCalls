#ifndef CALL_H
#define CALL_H

#include <QString>



class Call
{
public:
    int id;
    int hours;
    int minutes;
    int type;
    QString soundPatch;
    int saturday;
    Call(int,int, int, int, QString, int);
    Call();
};

#endif // CALL_H
