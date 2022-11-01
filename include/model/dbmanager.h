#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QtSql>
#include "include/viewmodel/call.h"

class DbManager
{
private:

    void static init(QSqlDatabase db);
    void static close(QSqlDatabase db);

public:







    void static insert(Call* call);

    void static remove(int);

    void static update(Call *call);

    static QList<Call*>* getListCall(int type, int special);

    static void Find(int , int ,int, int, bool&, Call&);

    static int getId(int index);

};

#endif // DBMANAGER_H
