#ifndef ISOTOPESDIAGRAMVIEW_H
#define ISOTOPESDIAGRAMVIEW_H


#include "isotopesview.h"
#include "isotopediagramitem.h"
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QScrollBar>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPolygonF>
#include <QPainterPath>
#include <QTransform>
#include <QVector>

class IsotopesDiagramView : public IsotopesView
{
    Q_OBJECT

public:
    explicit IsotopesDiagramView(int,QSqlQueryModel*,int,int,QWidget* = 0);
    void updateIsotopes(int =6);

signals:
    void isotopeSelectionChanged(int);

public slots:
    void changeIsotopeSelection(int);

protected:
    void generateElements();
    void wheelEvent(QWheelEvent*);
    void resizeEvent(QResizeEvent*);    
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void drawForeground(QPainter*,const QRectF&);

private slots:
    void sceneSelectionChanged();

private:
    static void adaptPenWidth(QPainter*,double);
    QPoint mouseLastPosition;

};

#endif // ISOTOPESDIAGRAMVIEW_H
