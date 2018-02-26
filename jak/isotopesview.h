#ifndef ISOTOPESVIEW_H
#define ISOTOPESVIEW_H

#include <QGraphicsView>
#include <QPair>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>
#include <QSize>
#include <QList>
#include <QStyleOptionGraphicsItem>
#include <QPalette>
#include <QSizePolicy>
#include <cmath>
#include <iostream>
#include <QGraphicsScene>

class IsotopesView : public QGraphicsView
{
    Q_OBJECT

public:
    enum GroupByKind
    {
        ISOTOPES=120,
        ISOBARES=300,
        ISOTONES=180
    };

    enum GroupByColumnId
    {
        ISOT=1,
        ISOB=3,
        ISON=2
    };

    explicit IsotopesView(int,QSqlQueryModel*,int,int,QWidget* =0,GroupByKind=ISOTOPES,GroupByColumnId=ISOT);
    virtual void updateIsotopes(int =6) =0;
    int heightForWidth(int) const;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    bool hasHeightForWidth() const;

protected:    
    virtual void generateElements() =0;
    QPair<double,double> minMax(QSqlQueryModel*,int,int);
    QSqlQueryModel* dataModel;
    double aspectRatio;
    int startIsotope;
    int columnId;
    GroupByKind maxX;
    GroupByColumnId columnZid;
    double factorX;

};

#endif // ISOTOPESVIEW_H



