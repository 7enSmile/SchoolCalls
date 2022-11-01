#include "../../include/model/dbmanager.h"

void DbManager::init(QSqlDatabase db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.db");
    db.open();


}

void DbManager::close(QSqlDatabase db)
{
    QString qs;
    qs.append(QSqlDatabase::database().connectionName());
    QSqlDatabase::removeDatabase(qs);
    db.close();



}


void DbManager::insert(Call *call)
{
    QSqlDatabase db;
    DbManager::init(db);
    QSqlQuery query(db);
    query.prepare(
                "INSERT INTO Calls(hours, minutes, type, soundpatch, saturday, special)"
                "VALUES(:hours, :minutes, :type, :soundpatch, :saturday, :special)"
                );
    query.bindValue(":hours", call->hours);
    query.bindValue(":minutes", call->minutes);
    query.bindValue(":type", call->type);
    query.bindValue(":soundpatch", call->soundPatch);
    query.bindValue(":saturday", call->saturday);
    query.bindValue(":special", call->special);
    query.exec();
    query.finish();
    DbManager::close(db);

}

void DbManager::remove(int id)
{
    QSqlDatabase db;
    DbManager::init(db);

    QSqlQuery query(db);
    QString str = QString("DELETE FROM Calls "
                          "WHERE id=%1").arg(id);
    query.exec(str);
    query.finish();
    DbManager::close(db);
}

void DbManager::update(Call *call)
{
    QSqlDatabase db;
    DbManager::init(db);
    QSqlQuery query(db);
    QString str = QString(
                "UPDATE Calls "
                "SET hours=%1, minutes=%2, type=%3, soundpatch='%4', saturday=%5, special=%6 "
                "WHERE id=%7"
                ).arg(call->hours).arg(call->minutes).arg(call->type).arg(call->soundPatch)
            .arg(call->saturday).arg(call->special).arg(call->id);
    query.exec(str);
    query.finish();
    DbManager::close(db);
}

QList<Call *>* DbManager::getListCall(int type, int special)
{
    QSqlDatabase db;
    DbManager::init(db);
    QList <Call*> *listOfCalls = new QList <Call*>();
    QSqlQuery query(db);
    QString str = QString("SELECT * FROM Calls "
                          "WHERE type=%1 and special=%2").arg(type).arg(special);
    query.exec(str);
    while(query.next()){
        int id = query.value(0).toInt();
        int hours = query.value(1).toInt();
        int minutes = query.value(2).toInt();
        int type = query.value(3).toInt();
        QString soundPatch = query.value(4).toString();
        int saturday = query.value(5).toInt();
        int special = query.value(6).toInt();
        Call *call = new Call(hours,minutes,type,soundPatch,saturday,special);
        call->id = id;
        listOfCalls->append(call);
    }
    query.finish();
    DbManager::close(db);
    return listOfCalls;
}

void DbManager::Find(int h, int m, int sp, int s, bool &flag, Call& call)
{
    QSqlDatabase db;
    DbManager::init(db);
    flag = false;
    QString str = QString("SELECT * FROM Calls "
                          "WHERE hours=%1 AND minutes=%2 AND special=%3 AND saturday=%4 ").arg(h).arg(m).arg(sp).arg(s);
    QSqlQuery query(db);
    if(query.exec(str)){
        if (query.next()){
            flag = true;
            call.id = query.value(0).toInt();
            call.hours = query.value(1).toInt();
            call.minutes = query.value(2).toInt();
            call.type = query.value(3).toInt();
            call.soundPatch = query.value(4).toString();
            call.saturday = query.value(5).toInt();
            call.special = query.value(6).toInt();
        }
    }
    query.finish();
    DbManager::close(db);

}

int DbManager::getId(int index)
{
    QSqlDatabase db;
    DbManager::init(db);
    QString str = QString("SELECT id FROM (SELECT  ROW_NUMBER() OVER (ORDER BY Id DESC)"
                          "AS ROW, * FROM Calls) "
                          );
    QSqlQuery query(db);
    query.exec(str);
    query.next();
    int id = query.value(0).toInt();
    DbManager::close(db);
    return id;
}
