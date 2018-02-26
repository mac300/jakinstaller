#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "isotopesdiagramview.h"
#include "isotopesgraphview.h"
#include "isotopewidget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QWidget>
#include <QTableView>
#include <QSqlQueryModel>
#include <QScrollBar>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QRadioButton>
#include <QButtonGroup>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(int,QSqlQueryModel*,QWidget* = 0);

signals:
    void tableRowChanged(int);

public slots:
    void updateIsotopes(const int);
    void exportGraphToPng();

private slots:
    void tableRowActivated(const QModelIndex&);

private:
    void changeDataModelLabel();
    QSqlQueryModel* dataModel;
    QTableView* dataView;
    IsotopesDiagramView* diagramView;
    IsotopesGraphView* graphView;
    IsotopeWidget* isotopeWidget;
    QButtonGroup* groupByOptions;
    QGroupBox* isotopesDiagramGroup;
    QGroupBox* isotopesTableGroup;
    QGroupBox* isotopesGraphGroup;
    int columnId;

};

#endif // MAINWIDGET_H
