#ifndef SELECTEDISOTOPELABEL_H
#define SELECTEDISOTOPELABEL_H

#include <QGraphicsItem>
#include <QCoreApplication>
#include <QApplication>
#include <QFont>
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QFontMetricsF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QString>
#include <QColor>

class SelectedIsotopeLabel : public QGraphicsItem
{
    Q_DECLARE_TR_FUNCTIONS(SelectedIsotopeLabel)

public:
    explicit SelectedIsotopeLabel(int,QString,QString,QString,QString,QColor);
    QRectF boundingRect() const;
    void paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget*);
    static double shift();

private:
    int labelType;
    QString smb;
    QString z;
    QString a;
    QString value;
    QColor color;

};

#endif // SELECTEDISOTOPELABEL_H
