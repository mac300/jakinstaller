#ifndef ELEMENTGRAPHICSITEM_H
#define ELEMENTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QString>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QColor>
#include <QPainterPath>
#include <QCoreApplication>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

class IsotopeDiagramItem : public QGraphicsItem
{
    Q_DECLARE_TR_FUNCTIONS(IsotopeDiagramItem)

public:
    explicit IsotopeDiagramItem(int,int,int,QString,QString);
    QRectF boundingRect() const;
    void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*);
    int getZ() const;
    int getN() const;
    int getIndex() const;
    QString getValue() const;
    void setValue(const QString);
    static void setIsotopeDiagramItem(const double,const double,const QString);
    static QPointF shift(QPointF);

private:
    void generateColor();
    int z;
    int n;
    int index;
    QString value;
    static double minValue;
    static double maxValue;
    static QString valueLabel;
    QString smb;
    QColor color;

};

#endif // ELEMENTGRAPHICSITEM_H
