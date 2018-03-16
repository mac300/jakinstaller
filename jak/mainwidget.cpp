#include "mainwidget.h"
#include <QHeaderView>

MainWidget::MainWidget(int start,QSqlQueryModel* model,QWidget* parent) :
    QWidget(parent)
{
    this->dataModel=model;
    this->changeDataModelLabel();
    this->columnId=6;
    QGridLayout* mainLayout=new QGridLayout(this);

    //Diagram izotopow
    this->isotopesDiagramGroup=new QGroupBox(tr("Isotopes mass excess"));
    QVBoxLayout* isotopesDiagramGroupLayout=new QVBoxLayout;
    this->isotopesDiagramGroup->setLayout(isotopesDiagramGroupLayout);
    this->diagramView=new IsotopesDiagramView(start,this->dataModel,6000,9000,this);
    isotopesDiagramGroupLayout->addWidget(this->diagramView);

    //Izotop Info
    this->isotopeWidget=new IsotopeWidget(start,model,this);
    QGroupBox* isotopeInfoGroup=new QGroupBox(tr("Isotope Info"));
    QVBoxLayout* isotopeInfoGroupLayout=new QVBoxLayout;
    isotopeInfoGroup->setLayout(isotopeInfoGroupLayout);
    isotopeInfoGroupLayout->addWidget(this->isotopeWidget);

    //Tabela z danymi
    this->isotopesTableGroup=new QGroupBox(tr("Table of mass excess value"));
    QHBoxLayout* isotopesTableGroupLayout=new QHBoxLayout;
    this->isotopesTableGroup->setLayout(isotopesTableGroupLayout);
    this->dataView=new QTableView(this);
    this->dataView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->dataView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->dataView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    this->dataView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->dataView->verticalHeader()->setVisible(false);
    this->dataView->setModel(this->dataModel);
    for(int i=0;i<this->dataModel->columnCount();++i)
    {
        if(i!=1&&i!=2&&i!=4&&i!=6&&i!=7)
        {
            this->dataView->setColumnHidden(i,true);
        }
        else
        {
            this->dataView->setColumnHidden(i,false);
        }
    }
    this->dataView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    this->dataView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    this->dataView->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    //this->dataView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    //this->dataView->setStyleSheet("text-align: center");
    this->dataView->selectRow(start);
    this->dataView->verticalScrollBar()->setValue(start-3);
    isotopesTableGroupLayout->addWidget(this->dataView);

    //Wykres
    this->isotopesGraphGroup=new QGroupBox(tr("Mass excess values"));
    QVBoxLayout* isotopesGraphGroupLayout=new QVBoxLayout;
    this->isotopesGraphGroup->setLayout(isotopesGraphGroupLayout);
    QHBoxLayout* graphOptionsLayout=new QHBoxLayout;
    QRadioButton* byIsotopes=new QRadioButton("group by isotopes");
    QRadioButton* byIsobares=new QRadioButton("group by isobares");
    QRadioButton* byIsotones=new QRadioButton("group by isotones");
    this->groupByOptions=new QButtonGroup(this);
    this->groupByOptions->addButton(byIsotopes,0);
    this->groupByOptions->addButton(byIsobares,1);
    this->groupByOptions->addButton(byIsotones,2);
    byIsotopes->setChecked(true);
    graphOptionsLayout->addStretch();
    graphOptionsLayout->addWidget(byIsotopes);
    graphOptionsLayout->addStretch();
    graphOptionsLayout->addWidget(byIsobares);
    graphOptionsLayout->addStretch();
    graphOptionsLayout->addWidget(byIsotones);
    graphOptionsLayout->addStretch();
    isotopesGraphGroupLayout->addLayout(graphOptionsLayout);
    this->graphView=new IsotopesGraphView(start,this->dataModel,1500,500,this);
    isotopesGraphGroupLayout->addWidget(this->graphView);

    mainLayout->addWidget(isotopesDiagramGroup,0,0,2,1);
    mainLayout->addWidget(isotopeInfoGroup,0,1,1,1);
    mainLayout->addWidget(isotopesTableGroup,0,2,1,1);
    mainLayout->addWidget(isotopesGraphGroup,1,1,1,2);
    mainLayout->setColumnStretch(0,1);
    mainLayout->setColumnMinimumWidth(1,500);
    mainLayout->setColumnStretch(1,0);
    mainLayout->setColumnMinimumWidth(2,380);
    mainLayout->setColumnStretch(2,1);
    mainLayout->setRowStretch(0,0);
    mainLayout->setRowStretch(1,2);

    connect(this->diagramView,SIGNAL(isotopeSelectionChanged(int)),this->isotopeWidget,SLOT(updateInfo(int)));
    connect(this->diagramView,SIGNAL(isotopeSelectionChanged(int)),this->dataView,SLOT(selectRow(int)));
    connect(this->diagramView,SIGNAL(isotopeSelectionChanged(int)),this->graphView,SLOT(updateSelected(int)));
    connect(this->isotopeWidget,SIGNAL(isotopeChanged(int)),this->diagramView,SLOT(changeIsotopeSelection(int)));
    connect(this->dataView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(tableRowActivated(QModelIndex)));
    connect(this,SIGNAL(tableRowChanged(int)),this->diagramView,SLOT(changeIsotopeSelection(int)));
    connect(this->groupByOptions,SIGNAL(buttonClicked(int)),this->graphView,SLOT(changeGroupBy(int)));

}

void MainWidget::updateIsotopes(const int columnId)
{
    switch (columnId)
    {
    case 8:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes binding energy"));
        this->isotopesTableGroup->setTitle(tr("Table of binding energy value"));
        this->isotopesGraphGroup->setTitle(tr("Binding energy values"));
        break;
    case 11:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes atomic mass"));
        this->isotopesTableGroup->setTitle(tr("Table of atomic mass value"));
        this->isotopesGraphGroup->setTitle(tr("Atomic mass values"));
        break;
    case 15:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes half life"));
        this->isotopesTableGroup->setTitle(tr("Table of half life value"));
        this->isotopesGraphGroup->setTitle(tr("Half life values"));
        break;
    case 20:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes \u03b2 decay energy"));
        this->isotopesTableGroup->setTitle(tr("Table of \u03b2 decay energy value"));
        this->isotopesGraphGroup->setTitle(tr("\u03b2 decay energy values"));
        break;
    case 22:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes 2n separation energy"));
        this->isotopesTableGroup->setTitle(tr("Table of 2n separation energy value"));
        this->isotopesGraphGroup->setTitle(tr("2n separation energy values"));
        break;
    case 24:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes 2p separation energy"));
        this->isotopesTableGroup->setTitle(tr("Table of 2p separation energy value"));
        this->isotopesGraphGroup->setTitle(tr("2p separation energy values"));
        break;
    case 26:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes 1n separation energy"));
        this->isotopesTableGroup->setTitle(tr("Table of 1n separation energy value"));
        this->isotopesGraphGroup->setTitle(tr("1n separation energy values"));
        break;
    case 28:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes 1p separation energy"));
        this->isotopesTableGroup->setTitle(tr("Table of 1p separation energy value"));
        this->isotopesGraphGroup->setTitle(tr("1p separation energy values"));
        break;
    case 30:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q \u03b1 energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q \u03b1 energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q \u03b1 energy values"));
        break;
    case 32:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q 2\u03b2 energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q 2\u03b2 energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q 2\u03b2 energy values"));
        break;
    case 34:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q ep energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q ep energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q ep energy values"));
        break;
    case 36:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q \u03b2n energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q \u03b2n energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q \u03b2n energy values"));
        break;
    case 38:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q 4\u03b2 energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q 4\u03b2 energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q 4\u03b2 energy values"));
        break;
    case 40:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q d\u03b1 energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q d\u03b1 energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q d\u03b1 energy values"));
        break;
    case 42:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q p\u03b1 energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q p\u03b1 energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q p\u03b1 energy values"));
        break;
    case 44:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes Q n\u03b1 energy"));
        this->isotopesTableGroup->setTitle(tr("Table of Q n\u03b1 energy value"));
        this->isotopesGraphGroup->setTitle(tr("Q n\u03b1 energy values"));
        break;
    default:
        this->isotopesDiagramGroup->setTitle(tr("Isotopes mass excess"));
        this->isotopesTableGroup->setTitle(tr("Table of mass excess value"));
        this->isotopesGraphGroup->setTitle(tr("Mass excess values"));
        break;
    }
    this->dataView->setColumnHidden(this->columnId,true);
    this->dataView->setColumnHidden(this->columnId+1,true);
    this->dataView->setColumnHidden(columnId,false);
    this->dataView->setColumnHidden(columnId+1,false);
    this->columnId=columnId;

    this->diagramView->updateIsotopes(columnId);

    this->graphView->updateIsotopes(columnId);

}

void MainWidget::tableRowActivated(const QModelIndex& current)
{
    emit this->tableRowChanged(current.row());
}

void MainWidget::changeDataModelLabel()
{
    this->dataModel->setHeaderData(1,Qt::Horizontal,tr("Z"));
    this->dataModel->setHeaderData(2,Qt::Horizontal,tr("N"));
    this->dataModel->setHeaderData(4,Qt::Horizontal,tr("Symbol"));
    this->dataModel->setHeaderData(6,Qt::Horizontal,tr("Mass Excess"));
    this->dataModel->setHeaderData(7,Qt::Horizontal,tr("\u0394 Of Mass Excess"));
    this->dataModel->setHeaderData(8,Qt::Horizontal,tr("Binding Energy"));
    this->dataModel->setHeaderData(9,Qt::Horizontal,tr("\u0394 Of Binding Energy"));
    this->dataModel->setHeaderData(11,Qt::Horizontal,tr("Atomic Mass"));
    this->dataModel->setHeaderData(12,Qt::Horizontal,tr("\u0394 Of Atomic Mass"));
    this->dataModel->setHeaderData(15,Qt::Horizontal,tr("Half Life"));
    this->dataModel->setHeaderData(16,Qt::Horizontal,tr("\u0394 Of Half Life"));
    this->dataModel->setHeaderData(20,Qt::Horizontal,tr("\u03b2 Decay Energy"));
    this->dataModel->setHeaderData(21,Qt::Horizontal,tr("\u0394 Of \u03b2 Decay Energy"));
    this->dataModel->setHeaderData(22,Qt::Horizontal,tr("2n Separation Energy"));
    this->dataModel->setHeaderData(23,Qt::Horizontal,tr("\u0394 Of 2n Separation Energy"));
    this->dataModel->setHeaderData(24,Qt::Horizontal,tr("2p Separation Energy"));
    this->dataModel->setHeaderData(25,Qt::Horizontal,tr("\u0394 Of 2p Separation Energy"));
    this->dataModel->setHeaderData(26,Qt::Horizontal,tr("1n Separation Energy"));
    this->dataModel->setHeaderData(27,Qt::Horizontal,tr("\u0394 Of 1n Separation Energy"));
    this->dataModel->setHeaderData(28,Qt::Horizontal,tr("1p Separation Energy"));
    this->dataModel->setHeaderData(29,Qt::Horizontal,tr("\u0394 Of 1p Separation Energy"));
    this->dataModel->setHeaderData(30,Qt::Horizontal,tr("\u03b1 Q-Value"));
    this->dataModel->setHeaderData(31,Qt::Horizontal,tr("\u0394 Of \u03b1 Q-Value"));
    this->dataModel->setHeaderData(32,Qt::Horizontal,tr("2\u03b2 Q-Value"));
    this->dataModel->setHeaderData(33,Qt::Horizontal,tr("\u0394 Of 2\u03b2 Q-Value"));
    this->dataModel->setHeaderData(34,Qt::Horizontal,tr("ep Q-Value"));
    this->dataModel->setHeaderData(35,Qt::Horizontal,tr("\u0394 Of ep Q-Value"));
    this->dataModel->setHeaderData(36,Qt::Horizontal,tr("\u03b2n Q-Value"));
    this->dataModel->setHeaderData(37,Qt::Horizontal,tr("\u0394 Of \u03b2n Q-Value"));
    this->dataModel->setHeaderData(38,Qt::Horizontal,tr("4\u03b2 Q-Value"));
    this->dataModel->setHeaderData(39,Qt::Horizontal,tr("\u0394 Of 4\u03b2 Q-Value"));
    this->dataModel->setHeaderData(40,Qt::Horizontal,tr("d\u03b1 Q-Value"));
    this->dataModel->setHeaderData(41,Qt::Horizontal,tr("\u0394 Of d\u03b1 Q-Value"));
    this->dataModel->setHeaderData(42,Qt::Horizontal,tr("p\u03b1 Q-Value"));
    this->dataModel->setHeaderData(43,Qt::Horizontal,tr("\u0394 Of p\u03b1 Q-Value"));
    this->dataModel->setHeaderData(44,Qt::Horizontal,tr("n\u03b1 Q-Value"));
    this->dataModel->setHeaderData(45,Qt::Horizontal,tr("\u0394 Of n\u03b1 Q-Value"));
}

void MainWidget::exportGraphToPng()
{
    this->graphView->exportGraph();

}













