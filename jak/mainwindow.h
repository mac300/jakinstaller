#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include "isotopeaction.h"
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QList>
#include <QProgressBar>
#include <iostream>

class MainWidget;
class IsotopeAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    QSqlQueryModel* getDataModel();
    QList<QAction*> getIsotopeActions() const;

private slots:
    void showInfo();

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
