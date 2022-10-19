#include "../../include/model/dbmanager.h"

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("db.db");
    m_db.open();
}

void DbManager::insert(Call *call)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO Calls(hours, minutes, type, soundpatch, saturday)"
        "VALUES(:hours, :minutes, :type, :soundpatch, :saturday)"
    );
    query.bindValue(":hours", call->hours);
    query.bindValue(":minutes", call->minutes);
    query.bindValue(":type", call->type);
    query.bindValue(":soundpatch", call->soundPatch);
    query.bindValue(":saturday", call->saturday);
    query.exec();

}

void DbManager::remove(int id)
{
    QSqlQuery query(m_db);
    QString str = QString("DELETE FROM Calls "
                    "WHERE id=%1").arg(id);
    query.exec(str);
}

void DbManager::update(Call *call)
{
    QSqlQuery query(m_db);
    QString str = QString(
        "UPDATE Calls "
        "SET hours=%1, minutes=%2, type=%3, soundpatch='%4', saturday =%5 "
        "WHERE id=%6"
    ).arg(call->hours).arg(call->minutes).arg(call->type).arg(call->soundPatch).arg(call->saturday).arg(call->id);
    qDebug()<<query.lastError();
}

QList<Call *>* DbManager::getListCall(int type)
{
    QList <Call*> *listOfCalls = new QList <Call*>();
    QSqlQuery query(m_db);
    QString str = QString("SELECT * FROM Calls "
                    "WHERE type=%1").arg(type);
    query.exec(str);
    while(query.next()){
        int id = query.value(0).toInt();
        int hours = query.value(1).toInt();
        int minutes = query.value(2).toInt();
        int type = query.value(3).toInt();
        QString soundPatch = query.value(4).toString();
        int saturday = query.value(5).toInt();
        Call *call = new Call(id,hours,minutes,type,soundPatch,saturday);
        listOfCalls->append(call);
    }
    return listOfCalls;
}

void DbManager::Find(int h, int m, bool &flag, Call& call)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.db");
    db.open();
    flag = false;
    QString str = QString("SELECT * FROM Calls "
                    "WHERE hours=%1 AND minutes=%2").arg(h).arg(m);
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
        }
    }
}
