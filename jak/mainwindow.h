#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include "isotopeaction.h"
#include "infodialog.h"
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QList>
#include <QProgressBar>
#include <iostream>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
    QSqlQueryModel* getDataModel();

private slots:
    void showInfo();
    void actionSelected(const IsotopeAction*);

private:
    void setConnectionToDatabase();
    void setMinSize();
    void createMenu();
    void createActions();

    QMenu* fileMenu;
    QMenu* isotopesMenu;
    QMenu* infoMenu;

    QSqlDatabase dataBase;
    QSqlQueryModel* dataModel;
    MainWidget* mainWidget;
    QProgressBar* progresBar;

};

#endif // MAINWINDOW_H
