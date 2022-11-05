#include "include/view/mainwindow.h"
#include "ui_mainwindow.h"

#include <qcheckbox.h>
#include <QtGui>


void MainWindow::addToTable(QTableWidget *table, CallsManager *callManager)
{



    table->insertRow(table->rowCount());
    QString patch;
    if (ui->comboBoxType->currentIndex()==0){

        table->setIndexWidget(
                    table->model()->index(table->rowCount()-1 , 2 ),
                    createCheckBoxWidget(0,callManager->type)
                    );
        table->setIndexWidget(
                    table->model()->index( table->rowCount()-1, 4 ),
                    createPushButton(callManager->type)
                    );





        if (table->rowCount()!=1){

            QString textH = table->item(table->rowCount()-2,0)->text();
            QString textM = table->item(table->rowCount()-2,1)->text();
            patch = table->item(table->rowCount()-2,3)->text();
            table->setItem(table->rowCount()-1,0,new QTableWidgetItem(textH));
            table->setItem(table->rowCount()-1,1,new QTableWidgetItem(textM));
            table->setItem(table->rowCount()-1,3,new QTableWidgetItem(patch));


        }else{

            table->setItem(table->rowCount()-1,0,new QTableWidgetItem("8"));
            table->setItem(table->rowCount()-1,1,new QTableWidgetItem("30"));
            patch = "";
            table->setItem(table->rowCount()-1,3,new QTableWidgetItem(patch));
        }

    } else {


        table->setIndexWidget(
                    table->model()->index( table->rowCount()-1, 3 ),
                    createPushButton(callManager->type)
                    );





        if (table->rowCount()!=1){

            QString textH = table->item(table->rowCount()-2,0)->text();
            QString textM = table->item(table->rowCount()-2,1)->text();
            patch = table->item(table->rowCount()-2,2)->text();
            table->setItem(table->rowCount()-1,0,new QTableWidgetItem(textH));
            table->setItem(table->rowCount()-1,1,new QTableWidgetItem(textM));
            table->setItem(table->rowCount()-1,2,new QTableWidgetItem(patch));


        }else{

            table->setItem(table->rowCount()-1,0,new QTableWidgetItem("8"));
            table->setItem(table->rowCount()-1,1,new QTableWidgetItem("30"));
            patch = "";
            table->setItem(table->rowCount()-1,2,new QTableWidgetItem(patch));
        }


    }




    callManager->insert(table->item(table->rowCount()-1,0)->text().toInt(),
                        table->item(table->rowCount()-1,1)->text().toInt(), patch, 0, callManager->special);





}

void MainWindow::configTable(QTableWidget * table, int type)
{


    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if (ui->comboBoxType->currentIndex()==0){
        table->setColumnCount(5);
        table->setHorizontalHeaderItem(0,new QTableWidgetItem("Часы"));
        table->setHorizontalHeaderItem(1,new QTableWidgetItem("Минуты"));
        table->setHorizontalHeaderItem(2,new QTableWidgetItem("Суббота"));
        table->setHorizontalHeaderItem(3,new QTableWidgetItem("Путь к файлу"));
        table->setHorizontalHeaderItem(4,new QTableWidgetItem(""));
    } else {

        table->setColumnCount(4);
        table->setHorizontalHeaderItem(0,new QTableWidgetItem("Часы"));
        table->setHorizontalHeaderItem(1,new QTableWidgetItem("Минуты"));
        table->setHorizontalHeaderItem(2,new QTableWidgetItem("Путь к файлу"));
        table->setHorizontalHeaderItem(3,new QTableWidgetItem(""));


    }
    table->setItemDelegateForColumn(0,new TableDelegate(23,table));
    table->setItemDelegateForColumn(1,new TableDelegate(59,table));
    //table->setColumnWidth(3,150);

    switch (type) {
    case 0:
        fillTable(table,m_toLessonCallsManager);
        break;
    case 1:
        fillTable(table,m_fromLessonCallsManager);
        break;
    case 2:
        fillTable(table,m_phyMinCallsManager);
    default:
        break;
    }

}

void MainWindow::fillTable(QTableWidget * table, CallsManager * callManager)
{
    table->setRowCount(0);
    int h;
    int m;
    int s;
    QString patch;
    table->setRowCount(callManager->count);
    if (ui->comboBoxType->currentIndex()==0){
        for (int i=0;i<callManager->count;i++){
            callManager->get(i,h,m,patch,s);

            table->setIndexWidget(
                        table->model()->index( i, 2 ),
                        createCheckBoxWidget(s,callManager->type)
                        );
            table->setIndexWidget(
                        table->model()->index( i, 4 ),
                        createPushButton(callManager->type)
                        );
            table->setItem(i, 0, new QTableWidgetItem(QString::number(h)));
            table->setItem(i, 1, new QTableWidgetItem(QString::number(m)));
            table->setItem(i, 3, new QTableWidgetItem(patch));
        }
    } else {

        for (int i=0;i<callManager->count;i++){
            callManager->get(i,h,m,patch,s);


            table->setIndexWidget(
                        table->model()->index( i, 3 ),
                        createPushButton(callManager->type)
                        );
            table->setItem(i, 0, new QTableWidgetItem(QString::number(h)));
            table->setItem(i, 1, new QTableWidgetItem(QString::number(m)));
            table->setItem(i, 2, new QTableWidgetItem(patch));
        }


    }

}

void MainWindow::removeFromTable(QTableWidget *table, CallsManager *callManager)
{
    if (callManager->count!=0){
        callManager->remove(table->rowCount()-1);
        table->removeRow(table->rowCount()-1);
    }



}

void MainWindow::updateTable(int index,int h, int m, QString p, CallsManager *callManager)
{

    callManager->update(index,h,m,p);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Звонки");
    ui->tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");
    m_toLessonCallsManager = new CallsManager(0,0);
    m_fromLessonCallsManager = new CallsManager(1,0);
    m_phyMinCallsManager = new CallsManager(2,0);
    configTable(ui->tableToLesson,0);
    configTable(ui->tableFromLesson,1);
    configTable(ui->tablePhysMin,2);
    QObject::connect(ui->addToLesson, SIGNAL(clicked()),this, SLOT(clickedAddToLesson()));
    QObject::connect(ui->removeToLesson, SIGNAL(clicked()),this, SLOT(clickedRemoveToLesson()));
    QObject::connect(ui->tableToLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableToLessonChanged);
    QObject::connect(ui->addFromLesson, &QAbstractButton::clicked,this, &MainWindow::clickedAddFromLesson);
    QObject::connect(ui->removeFromLesson, SIGNAL(clicked()),this, SLOT(clickedRemoveFromLesson()));
    QObject::connect(ui->tableFromLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableFromLessonChanged);
    QObject::connect(ui->addPhysMin, SIGNAL(clicked()),this, SLOT(clickedAddPhysMin()));
    QObject::connect(ui->tablePhysMin,&QTableWidget::itemChanged,
                     this, &MainWindow::tablePhysMinChanged);
    QObject::connect(ui->removePhysMin, SIGNAL(clicked()),this, SLOT(clickedRemovePhysMin()));
    QObject::connect(ui->pushButtonPatchToAllToLesson, SIGNAL(clicked()),
                     this, SLOT(clickedPatchToAllToLessonCall()));
    QObject::connect(ui->pushButtonPatchToAllFromLesson, SIGNAL(clicked()),
                     this, SLOT(clickedPatchToAllFromLessonCall()));
    QObject::connect(ui->pushButtonPatchToPhysMin, SIGNAL(clicked()),
                     this, SLOT(clickedPatchToAllPhysMin()));
    QObject::connect(ui->pushButtonTestSound, SIGNAL(clicked()),
                     this, SLOT(clickedPlaySoundTest()));
    QObject::connect(ui->pushButtonChangeWarningCall, SIGNAL(clicked()),
                     this, SLOT(clickedChangeWarningCall()));
    QObject::connect(ui->comboBoxType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(currentIndexChanged(int)));
    QSettings settings( "settings.conf", QSettings::IniFormat );
    settings.beginGroup( "WarningCall" );
    ui->lineEditWarningCall->setText(settings.value("patch",-1).toString());
    tmr = new QTimer();
    tmr->setInterval(30000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    updateTime();
    tmr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkClickToLesson(int)
{
    QCheckBox* cb = qobject_cast< QCheckBox* >(sender());
    QModelIndex index = ui->tableToLesson->indexAt( cb->parentWidget()->pos() );
    m_toLessonCallsManager->updateS(index.row());
}

void MainWindow::checkClickFromLesson(int)
{
    QCheckBox* cb = qobject_cast< QCheckBox* >(sender());
    QModelIndex index = ui->tableFromLesson->indexAt( cb->parentWidget()->pos() );
    m_fromLessonCallsManager->updateS(index.row());
}

void MainWindow::checkClickPhyMin(int)
{
    QCheckBox* cb = qobject_cast< QCheckBox* >(sender());
    QModelIndex index = ui->tablePhysMin->indexAt( cb->parentWidget()->pos() );
    m_phyMinCallsManager->updateS(index.row());
}

void MainWindow::clickedAddToLesson()
{
    QObject::disconnect(ui->tableToLesson,&QTableWidget::itemChanged,
                        this, &MainWindow::tableToLessonChanged);

    addToTable(ui->tableToLesson,m_toLessonCallsManager);

    QObject::connect(ui->tableToLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableToLessonChanged);
}

void MainWindow::clickedRemoveToLesson()
{
    removeFromTable(ui->tableToLesson,m_toLessonCallsManager);

}

void MainWindow::tableToLessonChanged(QTableWidgetItem *item)
{


    int index=item->row();
    int h = ui->tableToLesson->item(item->row(),0)->text().toInt();
    int m = ui->tableToLesson->item(item->row(),1)->text().toInt();
    QString p = ui->tableToLesson->item(item->row(),ui->tableToLesson->columnCount()-2)->text();
    updateTable(index,h,m,p,m_toLessonCallsManager);
}

void MainWindow::clickedAddFromLesson()
{
    QObject::disconnect(ui->tableFromLesson,&QTableWidget::itemChanged,
                        this, &MainWindow::tableFromLessonChanged);

    addToTable(ui->tableFromLesson,m_fromLessonCallsManager);

    QObject::connect(ui->tableFromLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableFromLessonChanged);
}

void MainWindow::clickedRemoveFromLesson()
{

    removeFromTable(ui->tableFromLesson,m_fromLessonCallsManager);
}

void MainWindow::tableFromLessonChanged(QTableWidgetItem * item)
{
    int index=item->row();
    int h = ui->tableFromLesson->item(item->row(),0)->text().toInt();
    int m = ui->tableFromLesson->item(item->row(),1)->text().toInt();
    QString p = ui->tableFromLesson->item(item->row(),ui->tableFromLesson->columnCount()-2)->text();
    updateTable(index,h,m,p,m_fromLessonCallsManager);

}

void MainWindow::clickedAddPhysMin()
{
    QObject::disconnect(ui->tablePhysMin,&QTableWidget::itemChanged,
                        this, &MainWindow::tablePhysMinChanged);

    addToTable(ui->tablePhysMin,m_phyMinCallsManager);

    QObject::connect(ui->tablePhysMin,&QTableWidget::itemChanged,
                     this, &MainWindow::tablePhysMinChanged);

}

void MainWindow::clickedRemovePhysMin()
{
    removeFromTable(ui->tablePhysMin,m_phyMinCallsManager);

}

void MainWindow::clicedPatchToLesson()
{
    QObject::disconnect(ui->tableToLesson,&QTableWidget::itemChanged,
                        this, &MainWindow::tableToLessonChanged);
    QPushButton* pb = qobject_cast< QPushButton* >(sender());
    QModelIndex index = ui->tableToLesson->indexAt( pb->parentWidget()->pos() );
    int h = ui->tableToLesson->item(index.row(),0)->text().toInt();
    int m = ui->tableToLesson->item(index.row(),1)->text().toInt();
    updatePatchToCall(index.row(),h,m,m_toLessonCallsManager,ui->tableToLesson);
    QObject::connect(ui->tableToLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableToLessonChanged);
}

void MainWindow::clicedPatchFromLesson()
{
    QObject::disconnect(ui->tableFromLesson,&QTableWidget::itemChanged,
                        this, &MainWindow::tableFromLessonChanged);
    QPushButton* pb = qobject_cast< QPushButton* >(sender());
    QModelIndex index = ui->tableFromLesson->indexAt( pb->parentWidget()->pos() );
    int h = ui->tableFromLesson->item(index.row(),0)->text().toInt();
    int m = ui->tableFromLesson->item(index.row(),1)->text().toInt();
    updatePatchToCall(index.row(),h,m,m_fromLessonCallsManager,ui->tableFromLesson);
    QObject::connect(ui->tableFromLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableFromLessonChanged);

}

void MainWindow::clicedPatchPhysMin()
{
    QObject::disconnect(ui->tablePhysMin,&QTableWidget::itemChanged,
                        this, &MainWindow::tablePhysMinChanged);
    QPushButton* pb = qobject_cast< QPushButton* >(sender());
    QModelIndex index = ui->tablePhysMin->indexAt( pb->parentWidget()->pos() );
    int h = ui->tablePhysMin->item(index.row(),0)->text().toInt();
    int m = ui->tablePhysMin->item(index.row(),1)->text().toInt();
    updatePatchToCall(index.row(),h,m,m_phyMinCallsManager,ui->tablePhysMin);
    QObject::connect(ui->tablePhysMin,&QTableWidget::itemChanged,
                     this, &MainWindow::tablePhysMinChanged);


}



void MainWindow::tablePhysMinChanged(QTableWidgetItem *item)
{
    int index=item->row();
    int h = ui->tablePhysMin->item(item->row(),0)->text().toInt();
    int m = ui->tablePhysMin->item(item->row(),1)->text().toInt();
    QString p = ui->tablePhysMin->item(item->row(),ui->tablePhysMin->columnCount()-2)->text();
    updateTable(index,h,m,p,m_phyMinCallsManager);

}

void MainWindow::clickedPatchToAllToLessonCall()
{
    QObject::disconnect(ui->tableToLesson,&QTableWidget::itemChanged,
                        this, &MainWindow::tableToLessonChanged);
    updatePatchToCallAll(m_toLessonCallsManager,ui->tableToLesson);
    QObject::connect(ui->tableToLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableToLessonChanged);


}

void MainWindow::clickedPatchToAllFromLessonCall()
{
    QObject::disconnect(ui->tableFromLesson,&QTableWidget::itemChanged,
                        this, &MainWindow::tableFromLessonChanged);
    updatePatchToCallAll(m_fromLessonCallsManager,ui->tableFromLesson);
    QObject::connect(ui->tableFromLesson,&QTableWidget::itemChanged,
                     this, &MainWindow::tableFromLessonChanged);

}

void MainWindow::clickedPatchToAllPhysMin()
{
    QObject::disconnect(ui->tablePhysMin,&QTableWidget::itemChanged,
                        this, &MainWindow::tablePhysMinChanged);
    updatePatchToCallAll(m_phyMinCallsManager,ui->tablePhysMin);
    QObject::connect(ui->tablePhysMin,&QTableWidget::itemChanged,
                     this, &MainWindow::tablePhysMinChanged);

}



QWidget* MainWindow::createCheckBoxWidget(int s, int type)
{
    QWidget *checkBoxWidget = new QWidget();
    QCheckBox *checkBox = new QCheckBox();
    QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(checkBox);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    if (s == 1){
        checkBox->setChecked(true);
    }else{
        checkBox->setChecked(false);
    }

    switch (type) {
    case 0:
        connect( checkBox, SIGNAL( stateChanged( int ) ), SLOT( checkClickToLesson(int) ) );
        break;
    case 1:
        connect( checkBox, SIGNAL( stateChanged( int ) ), SLOT( checkClickFromLesson(int) ) );
        break;
    case 2:
        connect( checkBox, SIGNAL( stateChanged( int ) ), SLOT( checkClickPhyMin(int) ) );
        break;
    default:
        break;
    }


    return checkBoxWidget;
}

QWidget* MainWindow::createPushButton(int type)
{
    QWidget *pushButtonWidget = new QWidget();
    QPushButton *pushButton = new QPushButton();
    QHBoxLayout *layoutCheckBox = new QHBoxLayout(pushButtonWidget);
    layoutCheckBox->addWidget(pushButton);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    pushButton->setText("Обзор");
    switch (type) {
    case 0:
        connect( pushButton, SIGNAL(clicked()), SLOT( clicedPatchToLesson() ) );
        break;
    case 1:
        connect( pushButton, SIGNAL(clicked()), SLOT( clicedPatchFromLesson() ) );
        break;
    case 2:
        connect( pushButton, SIGNAL(clicked()), SLOT( clicedPatchPhysMin() ) );
        break;
    default:
        break;
    }

    return pushButtonWidget;

}

void MainWindow::updatePatchToCall(int index, int h, int m,
                                   CallsManager *callManager,
                                   QTableWidget *table)
{
    QString p = QFileDialog::getOpenFileName(this,
                                             QString::fromUtf8("Открыть файл"),
                                             QDir::currentPath(),
                                             "Звуки (*.mp3 *.wav)");
    if (!p.isEmpty()){
        callManager->update(index,h,m,p);
        table->setItem(index,table->columnCount()-2,new QTableWidgetItem(p));
    }
}

void MainWindow::updatePatchToCallAll(CallsManager *callManager, QTableWidget *table)
{
    QString p = QFileDialog::getOpenFileName(this,
                                             QString::fromUtf8("Открыть файл"),
                                             QDir::currentPath(),
                                             "Звуки (*.mp3 *.wav)");
    if (!p.isEmpty()){

        int h;
        int m;

        for (int i = 0; i < table->rowCount(); i++){

            h = table->item(i,0)->text().toInt();
            m = table->item(i,1)->text().toInt();
            table->setItem(i,table->columnCount()-2,new QTableWidgetItem(p));
            callManager->update(i,h,m,p);

        }
    }


}

void MainWindow::playSound(QString patch)
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl(patch));
    player->setVolume(50);
    player->play();


}

void MainWindow::updateTime()
{

    QDate dateToday = QDate::currentDate();
    int date = QString::number(dateToday.dayOfWeek()).toInt();
    switch (date) {
    case 1:
        ui->dateLabel->setText("Понедельник");
        break;
    case 2:
        ui->dateLabel->setText("Вторник");
        break;
    case 3:
        ui->dateLabel->setText("Среда");
        break;
    case 4:
        ui->dateLabel->setText("Четверг");
        break;
    case 5:
        ui->dateLabel->setText("Пятница");
        break;
    case 6:
        ui->dateLabel->setText("Суббота");
        break;
    case 7:
        ui->dateLabel->setText("Воскресенье");
        break;
    default:
        break;
    }

    if(QTime::currentTime().minute() > 9){

        ui->timeLabel->setText(QString(
                                   QString::number(QTime::currentTime().hour())+
                                   ":")+
                               QString::number(QTime::currentTime().minute()));
    }else{
        ui->timeLabel->setText(QString(
                                   QString::number(QTime::currentTime().hour())+
                                   ":0")+
                               QString::number(QTime::currentTime().minute()));

    }

    if (QTime::currentTime().minute() != m_minutes && dateToday.dayOfWeek() != 7){


        m_minutes = QTime::currentTime().minute();
        m_hours = QTime::currentTime().hour();
        QString patch;
        int type;
        bool flag;
        switch (ui->comboBoxType->currentIndex()) {
        case 0:


            if (m_minutes + 3 < 60){
                if (dateToday.dayOfWeek() == 6){

                    CallsManager::Find(m_hours,m_minutes + 3, 0, 1, flag, patch, type);

                } else {

                    CallsManager::Find(m_hours,m_minutes + 3, 0, 0, flag, patch, type);

                }

                if (flag && type == 0){

                    playSound(ui->lineEditWarningCall->text());

                }

            } else {



                if (dateToday.dayOfWeek() == 6){

                    CallsManager::Find(m_hours + 1,(m_minutes + 3) - 60, 0, 1, flag, patch, type);

                } else {

                    CallsManager::Find(m_hours + 1,(m_minutes + 3) - 60, 0, 0, flag, patch, type);


                }


                if (flag && type == 0){

                    playSound(ui->lineEditWarningCall->text());

                }

            }

            if (dateToday.dayOfWeek() == 6){

                CallsManager::Find(m_hours,m_minutes, 0, 1, flag, patch, type);

            } else {

                CallsManager::Find(m_hours,m_minutes, 0, 0, flag, patch, type);

            }

            if (flag){

                playSound(patch);

            }

            break;


        case 1:



            if (m_minutes + 3 < 60){

                CallsManager::Find(m_hours,m_minutes + 3, 1, 0, flag, patch, type);

                if (flag && type == 0){

                    playSound(ui->lineEditWarningCall->text());

                }

            } else {


                CallsManager::Find(m_hours + 1,(m_minutes + 3) - 60, 1, 0, flag, patch, type);

                if (flag && type == 0){

                    playSound(ui->lineEditWarningCall->text());

                }
            }

            CallsManager::Find(m_hours,m_minutes, 1, 0, flag, patch, type);

            if (flag){

                playSound(patch);

            }

            break;

        default:
            break;

        }


    }


}

void MainWindow::clickedPlaySoundTest()
{
    playSound("qrc:/sound/ring.mp3");

}

void MainWindow::clickedChangeWarningCall()
{
    QString p = QFileDialog::getOpenFileName(this,
                                             QString::fromUtf8("Открыть файл"),
                                             QDir::currentPath(),
                                             "Звуки (*.mp3 *.wav)");
    if (!p.isEmpty()){

        QSettings settings( "settings.conf", QSettings::IniFormat );

        if (ui->comboBoxType->currentIndex() == 0 ){

            settings.beginGroup( "WarningCall" );

        } else {


            settings.beginGroup( "WarningCallSpecial" );

        }
        settings.setValue("patch", p);
        ui->lineEditWarningCall->setText(p);

    }


}

void MainWindow::currentIndexChanged(int index)
{
    if (index == 1 || index == 0){

        QSettings settings( "settings.conf", QSettings::IniFormat );

        if (index == 0 ){

            settings.beginGroup( "WarningCall" );


        } else {


            settings.beginGroup( "WarningCallSpecial" );

        }

        ui->lineEditWarningCall->setText(settings.value("patch",-1).toString());

        ui->tabWidget->setDisabled(false);

        QObject::disconnect(ui->tableToLesson,&QTableWidget::itemChanged,
                            this, &MainWindow::tableToLessonChanged);

        QObject::disconnect(ui->tableFromLesson,&QTableWidget::itemChanged,
                            this, &MainWindow::tableFromLessonChanged);

        QObject::disconnect(ui->tablePhysMin,&QTableWidget::itemChanged,
                            this, &MainWindow::tablePhysMinChanged);

        m_toLessonCallsManager = new CallsManager(0,index);

        m_fromLessonCallsManager = new CallsManager(1,index);

        m_phyMinCallsManager = new CallsManager(2,index);

        configTable(ui->tableToLesson,0);

        configTable(ui->tableFromLesson,1);

        configTable(ui->tablePhysMin,2);

        QObject::connect(ui->tablePhysMin,&QTableWidget::itemChanged,
                         this, &MainWindow::tablePhysMinChanged);

        QObject::connect(ui->tableFromLesson,&QTableWidget::itemChanged,
                         this, &MainWindow::tableFromLessonChanged);


        QObject::connect(ui->tableToLesson,&QTableWidget::itemChanged,
                         this, &MainWindow::tableToLessonChanged);

    } else {

        ui->tabWidget->setDisabled(true);
    }








}

