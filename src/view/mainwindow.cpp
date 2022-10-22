#include "include/view/mainwindow.h"
#include "ui_mainwindow.h"

#include <qcheckbox.h>


void MainWindow::addToTable(QTableWidget *table, CallsManager *callManager)
{



    table->insertRow(table->rowCount());

    table->setIndexWidget(
                table->model()->index(table->rowCount()-1 , 2 ),
                createCheckBoxWidget(1,callManager->type)
                );
    table->setIndexWidget(
                table->model()->index( table->rowCount()-1, 4 ),
                createPushButton(callManager->type)
                );



    QString patch;

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
    }



    callManager->insert(table->item(table->rowCount()-1,0)->text().toInt(),
                        table->item(table->rowCount()-1,1)->text().toInt(), patch, 1, callManager->special);





}

void MainWindow::configTable(QTableWidget * table, int type)
{

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setItemDelegateForColumn(0,new TableDelegate(24,table));
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
    int h;
    int m;
    int s;
    QString patch;
    table->setRowCount(callManager->count);
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

}

void MainWindow::removeFromTable(QTableWidget *table, CallsManager *callManager)
{
    if (table->rowCount()>0){
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

    tmr = new QTimer();
    tmr->setInterval(60000);
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
    QString p = ui->tableToLesson->item(item->row(),3)->text();
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
    QString p = ui->tableFromLesson->item(item->row(),3)->text();
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
    QPushButton* pb = qobject_cast< QPushButton* >(sender());
    QModelIndex index = ui->tableToLesson->indexAt( pb->parentWidget()->pos() );
    int h = ui->tableToLesson->item(index.row(),0)->text().toInt();
    int m = ui->tableToLesson->item(index.row(),1)->text().toInt();
    updatePatchToCall(index.row(),h,m,m_toLessonCallsManager,ui->tableToLesson);
}

void MainWindow::clicedPatchFromLesson()
{
    QPushButton* pb = qobject_cast< QPushButton* >(sender());
    QModelIndex index = ui->tableFromLesson->indexAt( pb->parentWidget()->pos() );
    int h = ui->tableFromLesson->item(index.row(),0)->text().toInt();
    int m = ui->tableFromLesson->item(index.row(),1)->text().toInt();
    updatePatchToCall(index.row(),h,m,m_fromLessonCallsManager,ui->tableFromLesson);

}

void MainWindow::clicedPatchPhysMin()
{
    QPushButton* pb = qobject_cast< QPushButton* >(sender());
    QModelIndex index = ui->tablePhysMin->indexAt( pb->parentWidget()->pos() );
    int h = ui->tablePhysMin->item(index.row(),0)->text().toInt();
    int m = ui->tablePhysMin->item(index.row(),1)->text().toInt();
    updatePatchToCall(index.row(),h,m,m_phyMinCallsManager,ui->tablePhysMin);

}



void MainWindow::tablePhysMinChanged(QTableWidgetItem *item)
{
    int index=item->row();
    int h = ui->tablePhysMin->item(item->row(),0)->text().toInt();
    int m = ui->tablePhysMin->item(item->row(),1)->text().toInt();
    QString p = ui->tablePhysMin->item(item->row(),3)->text();
    updateTable(index,h,m,p,m_phyMinCallsManager);

}

void MainWindow::clickedPatchToAllToLessonCall()
{
    updatePatchToCallAll(m_toLessonCallsManager,ui->tableToLesson);


}

void MainWindow::clickedPatchToAllFromLessonCall()
{
    updatePatchToCallAll(m_fromLessonCallsManager,ui->tableFromLesson);

}

void MainWindow::clickedPatchToAllPhysMin()
{
    updatePatchToCallAll(m_phyMinCallsManager,ui->tablePhysMin);

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
        table->setItem(index,3,new QTableWidgetItem(p));
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
            table->setItem(i,3,new QTableWidgetItem(p));
            callManager->update(i,h,m,p);

        }
    }


}

void MainWindow::playSound(QString patch)
{
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile(patch));

    player->play();

}

void MainWindow::updateTime()
{
    QDate dateToday = QDate::currentDate();
    int date = QString::number(dateToday.dayOfWeek()).toInt();
    switch (date) {
    case 1:
        ui->dateLabel->setText("Подельник");
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
}

void MainWindow::clickedPlaySoundTest()
{
    playSound("qrc:/sound/ring.mp3");

}

