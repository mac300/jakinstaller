#ifndef ISOTOPESGRAPHVIEW_H
#define ISOTOPESGRAPHVIEW_H

#include "isotopesview.h"
#include "selectedisotopelabel.h"
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFontMetricsF>
#include <QApplication>
#include <QFileDialog>
#include <QImage>
#include <QPainter>

class IsotopesGraphView : public IsotopesView
{
    Q_OBJECT

public:
    explicit IsotopesGraphView(int,QSqlQueryModel*,int,int,QWidget* = 0);
    void updateIsotopes(int=6);
    QString getGraphName() const;
    void exportGraph();

public slots:
    void updateSelected(int);
    void changeGroupBy(int);

protected:
    void generateElements();
    void resizeEvent(QResizeEvent*);
    void wheelEvent(QWheelEvent*);

private:
    void generateSelected();
    QGraphicsTextItem* maxText;
    QGraphicsTextItem* minText;
    QGraphicsTextItem* zeroText;
    QGraphicsTextItem* labelXaxisText;
    QGraphicsLineItem* axisLine;
    QList<QGraphicsLineItem*> scaleOfX;
    QList<QGraphicsTextItem*> labelOfScaleX;
    QGraphicsItem* selectedItem;
    QGraphicsItem* selectedXaxis;
    QGraphicsItem* selectedYaxis;
    SelectedIsotopeLabel* selectedIsotopeLabel;
    double zero;
    double min;
    double max;
};

#endif // ISOTOPESGRAPHVIEW_H
