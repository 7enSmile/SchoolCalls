#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "include/view/tabledelegate.h"
#include "include/viewmodel/callsmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    CallsManager *m_toLessonCallsManager;

    CallsManager *m_fromLessonCallsManager;

    CallsManager *m_phyMinCallsManager;

    void addToTable(QTableWidget*,CallsManager *);

    void configTable(QTableWidget*,int type);

    void fillTable(QTableWidget*, CallsManager *);

    void removeFromTable(QTableWidget*,CallsManager *);

    void updateTable(int index,int h, int s, QString p, CallsManager *);
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void checkClickToLesson(int);

    void checkClickFromLesson(int);

    void checkClickPhyMin(int);

    void clickedAddToLesson();

    void clickedRemoveToLesson();

    void tableToLessonChanged(QTableWidgetItem *);

private:

    Ui::MainWindow *ui;

    QWidget *createCheckBoxWidget(int, int type);
};
#endif // MAINWINDOW_H
