#include "isotopesdiagramview.h"


IsotopesDiagramView::IsotopesDiagramView(int start,QSqlQueryModel* model,int sceneWidth,int sceneHeight,QWidget *parent)
    :IsotopesView(start,model,sceneWidth,sceneHeight,parent)
{   
    this->setDragMode(ScrollHandDrag);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->generateElements();
    this->centerOn(this->scene()->selectedItems().at(0));

    connect(this->scene(),SIGNAL(selectionChanged()),this,SLOT(sceneSelectionChanged()));
}

void IsotopesDiagramView::wheelEvent(QWheelEvent* event)
{
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    double numDegrees=event->delta();
    double numSteps=numDegrees/150.0;
    double factor=std::pow(1.05,numSteps);
    if(this->mapToScene(this->rect()).boundingRect().contains(this->sceneRect()))
    {
        factor=factor<1?1:factor;
    }
    this->scale(factor,factor);
}

void IsotopesDiagramView::resizeEvent(QResizeEvent* event)
{    
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    if(this->mapToScene(this->rect()).boundingRect().contains(this->sceneRect()))
    {
        this->fitInView(this->sceneRect(),Qt::KeepAspectRatio);
    }
    else
    {
        double factor=1.0*event->size().width()/event->oldSize().width();
        if(factor>0)
        {
            this->scale(factor,factor);
        }
    }
    QGraphicsView::resizeEvent(event);
}

void IsotopesDiagramView::generateElements()
{
    int rowCount=this->dataModel->rowCount();
    QString label=this->dataModel->headerData(this->columnId,Qt::Horizontal).toString();
    QPair<double,double> minmax=this->minMax(this->dataModel,rowCount,this->columnId);
    IsotopeDiagramItem::setIsotopeDiagramItem(minmax.first,minmax.second,label);

    //dane izotopów
    for(int i=0;i<rowCount;++i)
    {
        int z=this->dataModel->record(i).value(1).toInt();
        int n=this->dataModel->record(i).value(2).toInt();
        QString smb=this->dataModel->record(i).value(4).toString();
        QString value="";
        if(!dataModel->record(i).value(this->columnId).isNull())
        {
            value=dataModel->record(i).value(this->columnId).toString();
        }
        IsotopeDiagramItem* elm=new IsotopeDiagramItem(i,z,n,smb,value);
        if(i==this->startIsotope)
        {
            elm->setSelected(true);
        }
        elm->setPos(50+z*this->factorX,this->scene()->height()-100-n*50);
        this->scene()->addItem(elm);
    }


}

void IsotopesDiagramView::drawForeground(QPainter* painter, const QRectF& rect)
{
    double x=rect.x();
    double y=rect.y();
    double w=rect.width();
    double h=rect.height();
    double margin=w/20;

    QColor hColor(Qt::darkGray);
    hColor.setAlpha(175);
    QColor lColor(Qt::white);
    lColor.setAlpha(175);

    painter->setPen(hColor);
    IsotopesDiagramView::adaptPenWidth(painter,margin);
    QBrush lBrush(lColor);
    QBrush hBrush(hColor);

    QRectF vertical(x+margin/2,y+margin/2,margin,2*margin);
    QRectF horizontal(x+w-5*margin/2,y+h-3*margin/2,2*margin,margin);
    painter->fillRect(vertical,lBrush);
    painter->fillRect(horizontal,lBrush);

    QVector<QPointF> points;
    QPainterPath pathZ;
    points.append(QPointF(x+w-3*margin/2,y+h-3*margin/2));
    points.append(QPointF(x+w-margin/2,y+h-margin));
    points.append(QPointF(x+w-3*margin/2,y+h-margin/2));
    pathZ.addPolygon(QPolygonF(points));
    pathZ.closeSubpath();
    painter->fillPath(pathZ,hBrush);
    points.clear();
    QPainterPath pathN;
    points.append(QPointF(x+margin,y+margin/2));
    points.append(QPointF(x+3*margin/2,y+3*margin/2));
    points.append(QPointF(x+margin/2,y+3*margin/2));
    pathN.addPolygon(QPolygonF(points));
    pathN.closeSubpath();
    painter->fillPath(pathN,hBrush);
    points.clear();

    QPainterPath pathTextZ;
    points.append(QPointF(x+w-17*margin/8,y+h-5*margin/4));
    points.append(QPointF(x+w-7*margin/4,y+h-5*margin/4));
    points.append(QPointF(x+w-17*margin/8,y+h-3*margin/4));
    points.append(QPointF(x+w-7*margin/4,y+h-3*margin/4));
    pathTextZ.addPolygon(QPolygonF(points));
    painter->drawPath(pathTextZ);
    points.clear();
    QPainterPath pathTextN;
    points.append(QPointF(x+13*margin/16,y+9*margin/4));
    points.append(QPointF(x+13*margin/16,y+7*margin/4));
    points.append(QPointF(x+19*margin/16,y+9*margin/4));
    points.append(QPointF(x+19*margin/16,y+7*margin/4));
    pathTextN.addPolygon(QPolygonF(points));
    painter->drawPath(pathTextN);
    points.clear();
}

void IsotopesDiagramView::adaptPenWidth(QPainter* painter,double margin)
{
    QPen pen=painter->pen();
    double factor=margin/QFontMetrics(qApp->font()).height();
    pen.setWidthF(pen.widthF()*factor);
    painter->setPen(pen);
}

void IsotopesDiagramView::updateIsotopes(int columnId)
{
    this->columnId=columnId;
    int rowCount=this->dataModel->rowCount();
    QString label=this->dataModel->headerData(this->columnId,Qt::Horizontal).toString();
    QPair<double,double> minmax=this->minMax(this->dataModel,rowCount,this->columnId);
    IsotopeDiagramItem::setIsotopeDiagramItem(minmax.first,minmax.second,label);

    QList<QGraphicsItem*> items=this->scene()->items(Qt::AscendingOrder);
    for(int i=0;i<rowCount;++i)
    {
        QString value="";
        if(!dataModel->record(i).value(this->columnId).isNull())
        {
            value=dataModel->record(i).value(this->columnId).toString();
        }
        IsotopeDiagramItem* item=dynamic_cast<IsotopeDiagramItem*>(items.at(i));
        item->setValue(value);
    }
    this->scene()->update();
}

void IsotopesDiagramView::mousePressEvent(QMouseEvent* event)
{
    if(!event->modifiers().testFlag(Qt::ControlModifier))
    {
        if(event->buttons().testFlag(Qt::RightButton))
        {
            this->mouseLastPosition=event->pos();
        }
        else
        {
            QGraphicsView::mousePressEvent(event);
        }
    }
    else
    {
        event->setAccepted(false);
    }
}

void IsotopesDiagramView::mouseReleaseEvent(QMouseEvent* event)
{
    if(!event->modifiers().testFlag(Qt::ControlModifier))
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    else
    {
        event->setAccepted(false);
    }
}

void IsotopesDiagramView::mouseMoveEvent(QMouseEvent* event)
{    
    if(event->buttons().testFlag(Qt::RightButton))
    {
        QScrollBar* horizontalBar=this->horizontalScrollBar();
        QScrollBar* verticalBar=this->verticalScrollBar();
        QPoint mv=event->pos()-this->mouseLastPosition;
        this->mouseLastPosition=event->pos();
        horizontalBar->setValue(horizontalBar->value()+(this->isRightToLeft()?mv.x():-mv.x()));
        verticalBar->setValue(verticalBar->value()-mv.y());
    }
    else
    {
        event->setAccepted(false);
    }
}

void IsotopesDiagramView::sceneSelectionChanged()
{
    QList<QGraphicsItem*> selectedItems=this->scene()->selectedItems();
    if(!selectedItems.isEmpty())
    {
        IsotopeDiagramItem* item=dynamic_cast<IsotopeDiagramItem*>(selectedItems.at(0));
        if(!this->rect().contains(this->mapFromScene(IsotopeDiagramItem::shift(item->pos()))))
        {
            this->centerOn(item);
        }
        this->startIsotope = item->getIndex();
        emit this->isotopeSelectionChanged(this->startIsotope);
    }
}

void IsotopesDiagramView::changeIsotopeSelection(int row)
{
    if(this->startIsotope!=row)
    {
        this->scene()->clearSelection();
        QGraphicsItem* item=this->scene()->items(Qt::AscendingOrder).at(row);
        if(!this->rect().contains(this->mapFromScene(IsotopeDiagramItem::shift(item->pos()))))
        {
            this->centerOn(item);
        }
        item->setSelected(true);
    }
}

