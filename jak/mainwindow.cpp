#include "mainwindow.h"
#include <QMenuBar>
#include <QTabBar>
#include <QStatusBar>
#include <QDesktopWidget>
#include <QSize>
#include <QSqlError>
#include <QMessageBox>
#include <QIcon>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("J.A.K");
    this->setWindowIcon(QIcon(":/icons/logo.png"));
    this->setMinSize();

    this->setConnectionToDatabase();

    this->mainWidget=new MainWidget(59,this->dataModel,this);
    this->setCentralWidget(this->mainWidget);

    this->createMenu();
    this->createActions();

    this->statusBar()->showMessage(tr("Application ready"),5000);

}

MainWindow::~MainWindow(){}

QSqlQueryModel* MainWindow::getDataModel()
{
    return this->dataModel;
}

void MainWindow::setMinSize()
{
    QSize size=QDesktopWidget().size();
    int posX = 0;
    int posY = 0;
    if (size.width()>1280)
    {
        posX = size.width()/8;
        posY = size.height()/8;
        size.setHeight(3*size.height()/4);
        size.setWidth(3*size.width()/4);

    }
    this->setGeometry(posX,posY,size.width(),size.height());
    this->setMinimumSize(size);
}

void MainWindow::createMenu()
{
    this->fileMenu=this->menuBar()->addMenu(tr("&File"));
    this->isotopesMenu=this->menuBar()->addMenu(tr("Iso&topes"));
    this->infoMenu=this->menuBar()->addMenu(tr("&Info"));
}

void MainWindow::createActions()
{
    //File menu:

    QAction* action=new QAction(QIcon(tr(":/icons/export.png")),tr("Export to &file"),this);
    action->setStatusTip(tr("Export actual graph to png file"));
    connect(action,SIGNAL(triggered()),this->mainWidget,SLOT(exportGraphToPng()));
    this->fileMenu->addAction(action);

    this->fileMenu->addSeparator();

    action=new QAction(QIcon(tr(":/icons/exit.png")),tr("&Exit"),this);
    action->setStatusTip(tr("Close program imidietly"));
    connect(action,SIGNAL(triggered()),this,SLOT(close()));
    this->fileMenu->addAction(action);

    //Isotopes menu:

    IsotopeAction* isotopeAction=new IsotopeAction(IsotopeAction::MASS_EXCESS,tr("&Mass Excess"),this);
    isotopeAction->setStatusTip(tr("Show mass excess data"));
    isotopeAction->setEnabled(false);
    isotopeAction->setChecked(true);
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::BINDING_ENERGY,tr("&Binding Energy"),this);
    isotopeAction->setStatusTip(tr("Show binding energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::ATOMIC_MASS,tr("&Atomic Mass"),this);
    isotopeAction->setStatusTip(tr("Show atomic mass data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::HALF_LIFE,tr("&Half Life"),this);
    isotopeAction->setStatusTip(tr("Show half life time data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::BETA_DECAY_ENERGY,tr("\u03b2 &Decay Energy"),this);
    isotopeAction->setStatusTip(tr("Show \u03b2 decay energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    this->isotopesMenu->addSeparator();

    isotopeAction=new IsotopeAction(IsotopeAction::N2_SEPARATION,tr("2&n Separation Energy"),this);
    isotopeAction->setStatusTip(tr("Show 2n separation energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::P2_SEPARATION,tr("2&p Separation Energy"),this);
    isotopeAction->setStatusTip(tr("Show 2p separation energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::N_SEPARATION,tr("1n S&eparation Energy"),this);
    isotopeAction->setStatusTip(tr("Show 1n separation energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::P_SEPARATION,tr("1p Separa&tion Energy"),this);
    isotopeAction->setStatusTip(tr("Show 1p separation energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    this->isotopesMenu->addSeparator();

    isotopeAction=new IsotopeAction(IsotopeAction::Q_A,tr("\u03b1 Q-V&alue"),this);
    isotopeAction->setStatusTip(tr("Show \u03b1 Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_2B,tr("2\u03b2 Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show 2\u03b2 Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_EP,tr("ep Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show ep Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_BN,tr("\u03b2n Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show \u03b2n Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_4B,tr("4\u03b2 Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show 4\u03b2 Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_DA,tr("d\u03b1 Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show d\u03b1 Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_PA,tr("p\u03b1 Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show p\u03b1 Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    isotopeAction=new IsotopeAction(IsotopeAction::Q_NA,tr("n\u03b1 Q-Value"),this);
    isotopeAction->setStatusTip(tr("Show n\u03b1 Q-value energy data"));
    this->isotopesMenu->addAction(isotopeAction);

    foreach (QAction* act,this->isotopesMenu->actions())
    {
        act=dynamic_cast<IsotopeAction*>(act);
        if(act!=nullptr)
        {
            connect(act,SIGNAL(actionSelected(const IsotopeAction*)),this,SLOT(actionSelected(const IsotopeAction*)));
            connect(act,SIGNAL(actionSelected(const int)),mainWidget,SLOT(updateIsotopes(const int)));
        }
    }

    //Info menu:

    action=new QAction(QIcon(tr(":/icons/info.png")),tr("&Jak - information"),this);
    action->setStatusTip(tr("Informations about aplication J.a.k"));
    connect(action,SIGNAL(triggered()),this,SLOT(showInfo()));
    this->infoMenu->addAction(action);

}

void MainWindow::setConnectionToDatabase()
{
    this->dataBase=QSqlDatabase::addDatabase("QSQLITE");
    this->dataBase.setDatabaseName("./isotopes/isotopes.db");
    this->dataModel=new QSqlQueryModel;
    if(!this->dataBase.isOpen())
    {
        if(this->dataBase.open())
        {
            this->dataModel->setQuery("SELECT * FROM elements ORDER BY z,n");
            if(this->dataModel->lastError().isValid())
            {
                QMessageBox::warning(this,tr("Warning!"),this->dataModel->lastError().databaseText());
            }
            else
            {
                while(this->dataModel->canFetchMore())
                {
                    this->dataModel->fetchMore();
                }
                //QMessageBox::information(this,tr("Information!"),tr("Isotopes data loaded."));
            }
            this->dataBase.close();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning!"),tr("Connection error!"),QMessageBox::Ok);
        }
    }
}

void MainWindow::showInfo()
{    
    InfoDialog info(tr("J.A.K - info"),tr(":/text/readme.txt"),tr(":/icons/logo.png"),this->windowIcon());
    info.setModal(true);
    info.exec();
}

void MainWindow::actionSelected(const IsotopeAction* action)
{
    foreach (QAction* act,this->isotopesMenu->actions())
    {
        act=dynamic_cast<IsotopeAction*>(act);
        if(act!=nullptr)
        {
            if(act!=action)
            {
                act->setEnabled(true);
                act->setChecked(false);
            }
            else
            {
                act->setEnabled(false);
                act->setChecked(true);
            }
        }
    }
}














