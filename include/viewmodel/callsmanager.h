#ifndef CALLSMANAGER_H
#define CALLSMANAGER_H
#include "include/viewmodel/call.h"
#include "include/model/dbmanager.h"

class CallsManager
{
private:

    DbManager* m_dbmanager;

    QList<Call*> *m_listOfCalls;

public:
    int count;

    int type;

    CallsManager(int type_,int special);

    void insert(int h, int m, QString p, int s, int spt);

    void remove(int index);

    void update(int index, int h, int m, QString p);

    void updateS(int index);

    static void Find(int h, int m, int s, bool& flag, QString&p);

    void get(int index, int&h, int&m, int& s);

};

#endif // CALLSMANAGER_H
