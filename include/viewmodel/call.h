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

    int special;

    Call(int, int, int, QString, int, int);

    Call();
};

#endif // CALL_H
