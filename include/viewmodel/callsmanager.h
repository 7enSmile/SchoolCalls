#ifndef CALLSMANAGER_H
#define CALLSMANAGER_H
#include "include/viewmodel/call.h"
#include "include/model/dbmanager.h"
#include <QList>
class CallsManager
{
private:

    DbManager* m_dbmanager;

    QList<Call*> *m_listOfCalls;

public:
    int count;

    int type;

    int special;

    CallsManager(int type_,int special);

    void insert(int h, int m, QString p, int s, int spt);

    void remove(int index);

    void update(int index, int h, int m, QString p);

    void updateS(int index);

    static void Find(int h, int m, int sp, int s, bool& flag, QString&p, int &type);

    void get(int index, int&h, int&m, QString&p, int& s);

};

#endif // CALLSMANAGER_H
