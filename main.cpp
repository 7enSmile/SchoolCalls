#include "include/view/mainwindow.h"

#include <QApplication>
#include "include/viewmodel/call.h"
#include "include/model/dbmanager.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    //Call *call = new Call(10,15,0,"1.mp3");
    DbManager *dbmanager = new DbManager();
    //dbmanager->insert(call);
    //dbmanager->remove(2);
    //call->id = 3;
    //dbmanager->update(call);
    //QList <Call*> *listOfCalls = dbmanager->getListCall(0);
    //qDebug()<<listOfCalls->at(0)->soundPatch;
    Call call;
    bool flag;
    DbManager::Find(10,15, flag,call);
    if (flag){

        qDebug()<< call.saturday;
    }


}
