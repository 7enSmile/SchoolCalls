#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QtGui>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "include/view/tabledelegate.h"
#include "include/viewmodel/callsmanager.h"
#include <QSound>
#include <QSettings>

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

    Ui::MainWindow *ui;

    QWidget *createCheckBoxWidget(int, int type);

    QWidget* createPushButton(int type);

    void updatePatchToCall(int index, int h, int m, CallsManager *callManager,
                           QTableWidget* table);
    void updatePatchToCallAll(CallsManager *callManager,
                           QTableWidget* table);

    QTimer *tmr;

    int m_minutes = 0;
    int m_hours = 0;

    void playSound(QString patch);

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

    void clickedAddFromLesson();

    void clickedRemoveFromLesson();

    void tableFromLessonChanged(QTableWidgetItem *);

    void clickedAddPhysMin();

    void clickedRemovePhysMin();

    void clicedPatchToLesson();

    void clicedPatchFromLesson();

    void clicedPatchPhysMin();

    void tablePhysMinChanged(QTableWidgetItem *);

    void clickedPatchToAllToLessonCall();

    void clickedPatchToAllFromLessonCall();

    void clickedPatchToAllPhysMin();

    void updateTime();

    void clickedPlaySoundTest();

    void clickedChangeWarningCall();



};
#endif // MAINWINDOW_H
