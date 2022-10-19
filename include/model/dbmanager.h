#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "include/viewmodel/call.h"

class DbManager
{
private:
    QSqlDatabase m_db;

public:
    DbManager();
    void insert(Call* call);
    void remove(int id);
    void update(Call *call);
    QList<Call*>* getListCall(int type);
    static void Find(int, int ,bool&, Call&);

};

#endif // DBMANAGER_H
