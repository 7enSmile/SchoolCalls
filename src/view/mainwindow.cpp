#include "include/view/mainwindow.h"
#include "ui_mainwindow.h"

#include <qcheckbox.h>


void MainWindow::addToTable(QTableWidget *table, CallsManager *callManager)
{
    QObject::disconnect(table,SIGNAL
                        (itemChanged(QTableWidgetItem *)), this,
                        SLOT(tableToLessonChanged(QTableWidgetItem *)));
    table->insertRow(table->rowCount());

    table->setIndexWidget(
        table->model()->index(table->rowCount()-1 , 2 ),
        createCheckBoxWidget(1,callManager->type)
    );



    if (table->rowCount()!=1){

        QString textH = table->item(table->rowCount()-2,0)->text();
        QString textM = table->item(table->rowCount()-2,1)->text();
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem(textH));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem(textM));
    }else{
        qDebug()<<table->rowCount();
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem("8"));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem("30"));
    }


    callManager->insert(table->item(table->rowCount()-1,0)->text().toInt(), table->item(table->rowCount()-1,1)->text().toInt(), "1.mp3", 1, 0);

    QObject::connect(table,SIGNAL
                     (itemChanged(QTableWidgetItem *)), this,
                     SLOT(tableToLessonChanged(QTableWidgetItem *)));


}

void MainWindow::configTable(QTableWidget * table, int type)
{

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setItemDelegateForColumn(0,new TableDelegate(24,table));
    table->setItemDelegateForColumn(1,new TableDelegate(60,table));
    qDebug()<<type;
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
    table->setRowCount(callManager->count);
    for (int i=0;i<callManager->count;i++){
        callManager->get(i,h,m,s);

        table->setIndexWidget(
            table->model()->index( i, 2 ),
            createCheckBoxWidget(s,callManager->type)
        );
        table->setItem(i, 0, new QTableWidgetItem(QString::number(h)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(m)));
    }

}

void MainWindow::removeFromTable(QTableWidget *table, CallsManager *callManager)
{
    callManager->remove(table->rowCount()-1);
    table->removeRow(table->rowCount()-1);



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
    ui->tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");
    m_toLessonCallsManager = new CallsManager(0,0);
    m_fromLessonCallsManager = new CallsManager(1,0);
    m_phyMinCallsManager = new CallsManager(2,0);
    configTable(ui->tableToLesson,0);
    configTable(ui->tableFromLesson,1);
    configTable(ui->tablePhysMin,2);
    QObject::connect(ui->addToLesson, SIGNAL(clicked()),this, SLOT(clickedAddToLesson()));
    QObject::connect(ui->removeToLesson, SIGNAL(clicked()),this, SLOT(clickedRemoveToLesson()));
    QObject::connect(ui->tableToLesson,SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableToLessonChanged(QTableWidgetItem *)));




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
    qDebug()<<"checkClickFromLesson";
}

void MainWindow::checkClickPhyMin(int)
{
    qDebug()<<"checkClickPhyMin";
}

void MainWindow::clickedAddToLesson()
{
    addToTable(ui->tableToLesson,m_toLessonCallsManager);

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
    QString p = ui->lineEditPathtoLesson->text();
    updateTable(index,h,m,p,m_toLessonCallsManager);
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

