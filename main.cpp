#include "include/view/mainwindow.h"

#include <QApplication>
#include "include/viewmodel/call.h"
#include "include/model/dbmanager.h"
#include "include/viewmodel/call.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //Call *call = new Call(11,30,0,"1.mp3",0,0);
    //DbManager *dbmanager = new DbManager();
    //dbmanager->insert(call);
    //dbmanager->remove(2);
    //call->id = 3;
    //dbmanager->update(call);
    //QList <Call*> *listOfCalls = dbmanager->getListCall(0);
    //qDebug()<<listOfCalls->at(0)->soundPatch;
    //Call call;
    //bool flag;
    //DbManager::Find(10,15,0,flag,call);
    //if (flag){
        //DbManager *dbmanager = new DbManager();
        //qDebug()<< dbmanager->getId(&call);
    //}


}
