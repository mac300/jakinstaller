#include "isotopesview.h"

IsotopesView::IsotopesView(int start,QSqlQueryModel* model,int sceneWidth,int sceneHeight,QWidget* parent,GroupByKind groupBy,GroupByColumnId columnBy) :
    QGraphicsView(parent)
{
    this->startIsotope=start;
    this->dataModel=model;
    this->columnId=6;
    this->setScene(new QGraphicsScene(0,0,sceneWidth,sceneHeight,this));
    this->aspectRatio=1.0*sceneHeight/sceneWidth;
    this->maxX=groupBy;
    this->columnZid=columnBy;
    this->factorX=(this->scene()->width()-100)/this->maxX;

    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    this->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

}

QPair<double,double> IsotopesView::minMax(QSqlQueryModel* dataModel,int rowCoutn,int columnId)
{
    QList<double> list;
    double value;
    for(int i=0;i<rowCoutn;++i)
    {
        if(!dataModel->record(i).value(columnId).isNull()&&dataModel->record(i).value(columnId).toString()!="Inf")
        {
            value=dataModel->record(i).value(columnId).toString().toDouble();
            list.append(value);
        }
    }
    if(list.size()%2)
    {
        list.append(value);
    }
    double min,max;
    if(list.at(0)>list.at(1))
    {
        min=list.at(1);
        max=list.at(0);
    }
    else
    {
        min=list.at(0);
        max=list.at(1);
    }
    for(int i=2;i<list.size();i+=2)
    {
        if(list.at(i)>list.at(i+1))
        {
            if(list.at(i)>max) max=list.at(i);
            if(list.at(i+1)<min) min=list.at(i+1);
        }
        else
        {
            if(list.at(i+1)>max) max=list.at(i+1);
            if(list.at(i)<min) min=list.at(i);
        }
    }
    return QPair<double,double>(min,max);
}

int IsotopesView::heightForWidth(int w) const
{
    return (int)(w*(this->aspectRatio));
}

QSize IsotopesView::minimumSizeHint() const
{
    int w=QGraphicsView::minimumSizeHint().width();
    return QSize(w,this->heightForWidth(w));
}

QSize IsotopesView::sizeHint() const
{
    int w=QGraphicsView::sizeHint().width();
    return QSize(w,this->heightForWidth(w));
}

bool IsotopesView::hasHeightForWidth() const
{
    return true;
}


