#include "isotopesgraphview.h"
#include <QGraphicsTextItem>
#include <QPen>
#include <QColor>
#include <QGraphicsRectItem>

IsotopesGraphView::IsotopesGraphView(int start,QSqlQueryModel* model,int sceneWidth,int sceneHeight,QWidget *parent)
    :IsotopesView(start,model,sceneWidth,sceneHeight,parent)
{
    this->setDragMode(NoDrag);
    this->setInteractive(false);
    this->scene()->setBackgroundBrush(Qt::white);
    this->selectedItem=NULL;
    this->selectedXaxis=NULL;
    this->selectedYaxis=NULL;
    this->selectedIsotopeLabel=NULL;
    this->generateElements();
}

void IsotopesGraphView::generateElements()
{
    int rowCount=this->dataModel->rowCount();
    QPair<double,double> minmax=this->minMax(this->dataModel,rowCount,this->columnId);
    this->zero=0;
    QGraphicsRectItem* point;

    this->max=minmax.second;
    this->min=minmax.first;

    //dane izotopów
    for(int i=0;i<rowCount;++i)
    {
        int z=this->dataModel->record(i).value(this->columnZid).toInt();
        QString value="";
        if(!dataModel->record(i).value(this->columnId).isNull())
        {
            if(dataModel->record(i).value(15).toString()=="Inf")
            {
                point=this->scene()->addRect(QRectF(-2.5,-2.5,5,5),QPen(QColor(50,50,50)),QBrush(QColor(50,50,50)));
            }
            else
            {
                point=this->scene()->addRect(QRectF(-1,-1,2,2),QPen(QColor(100,100,100)),QBrush(QColor(100,100,100)));

            }
            value=dataModel->record(i).value(this->columnId).toString();
            if(value!="")
            {
                point->setPos(50+z*this->factorX,50+(this->scene()->height()-100)*(this->max-value.toDouble())/(this->max-this->min));
            }
            else
            {
                point->setPos(50+z*this->factorX,this->scene()->height()-50);
                point->setVisible(false);
            }
        }
    }

    //uklad wspolrzednych
    double rectHeight=1.0*(this->scene()->height()-100)/300;
    QColor rectColor;
    for(int i=0;i<300;++i)
    {
        rectColor.setHsv(i,255,255);
        this->scene()->addRect(20,(this->scene()->height()-50)-rectHeight*(i+1),30,rectHeight,QPen(rectColor),QBrush(rectColor));

    }

    this->minText=this->scene()->addText(tr("%1").arg(minmax.first));
    this->minText->setPos(20,this->scene()->height()-50);
    this->maxText=this->scene()->addText(tr("%1").arg(minmax.second));
    this->maxText->setPos(20,30);
    if(this->min*this->max<0)
    {
        this->zero=(this->scene()->height()-100)*this->max/(this->max-this->min);
    }
    else
    {
        this->zero=this->scene()->height()-100;
    }
    this->scene()->addLine(50,50,50,this->scene()->height()-50,QPen(QColor(Qt::black)));
    this->scene()->addLine(this->scene()->width()-50,50,this->scene()->width()-50,this->scene()->height()-50,QPen(QColor(Qt::black)));
    this->zeroText=this->scene()->addText("0");
    this->zeroText->setPos(5,37.5+this->zero);
    this->labelXaxisText=this->scene()->addText("Z");
    this->labelXaxisText->setPos(this->scene()->width()-45,37.5+this->zero);

    QPen pen(Qt::DashLine);
    this->axisLine=this->scene()->addLine(20,50+this->zero,this->scene()->width()-50,50+this->zero,pen);
    pen.setColor(Qt::lightGray);
    this->scene()->addLine(50,this->scene()->height()-50,this->scene()->width()-50,this->scene()->height()-50,pen);
    this->scene()->addLine(50,50,this->scene()->width()-50,50,pen);
    QGraphicsTextItem* textItem;
    QGraphicsLineItem* lineItem;
    for(int i=10;i<this->maxX;i+=10)
    {
        lineItem=this->scene()->addLine(50+i*this->factorX,40,50+i*this->factorX,this->scene()->height()-40,pen);
        this->scaleOfX.append(lineItem);
        textItem=this->scene()->addText(tr("%1").arg(i));
        textItem->setPos(55+i*this->factorX,this->scene()->height()-50);
        this->labelOfScaleX.append(textItem);
        textItem=this->scene()->addText(tr("%1").arg(i));
        textItem->setPos(55+i*this->factorX,30);
        this->labelOfScaleX.append(textItem);
    }

    this->scene()->addLine(20,50,75,50,QPen(QColor(Qt::black)));
    this->scene()->addLine(20,this->scene()->height()-50,75,this->scene()->height()-50,QPen(QColor(Qt::black)));
    this->scene()->addLine(this->scene()->width()-50,50,this->scene()->width()-75,50,QPen(QColor(Qt::black)));
    this->scene()->addLine(this->scene()->width()-50,this->scene()->height()-50,this->scene()->width()-75,this->scene()->height()-50,QPen(QColor(Qt::black)));

    //zaznaczenie
    this->generateSelected();

    this->scene()->update();

}

void IsotopesGraphView::generateSelected()
{
    if(this->selectedXaxis)
    {
        this->scene()->removeItem(this->selectedXaxis);
        delete this->selectedXaxis;
        this->selectedXaxis=NULL;
    }
    if(this->selectedYaxis)
    {
        this->scene()->removeItem(this->selectedYaxis);
        delete this->selectedYaxis;
        this->selectedYaxis=NULL;
    }
    if(this->selectedItem)
    {
        this->scene()->removeItem(this->selectedItem);
        delete this->selectedItem;
        this->selectedItem=NULL;
    }
    if(this->selectedIsotopeLabel)
    {
        this->scene()->removeItem(this->selectedIsotopeLabel);
        delete this->selectedIsotopeLabel;
        this->selectedIsotopeLabel=NULL;
    }
    QString selectedZ=this->dataModel->record(this->startIsotope).value(this->columnZid).toString();
    QString selectedTextZ=this->dataModel->record(this->startIsotope).value(1).toString();
    QString selectedTextA=this->dataModel->record(this->startIsotope).value(3).toString();
    QString selectedName=this->dataModel->record(this->startIsotope).value(46).toString();
    QString selectedValue="";
    if(!dataModel->record(this->startIsotope).value(this->columnId).isNull())
    {
        selectedValue=dataModel->record(this->startIsotope).value(this->columnId).toString();
        if(selectedValue=="Inf")
        {
            selectedValue="";
        }
    }
    if(selectedValue!="")
    {
        QPen pen(Qt::DashLine);
        pen.setColor(Qt::darkBlue);
        double x=50+this->factorX*selectedZ.toInt();
        double y=selectedValue.toDouble();
        if(this->columnId==15)
        {
            y=std::log10(y-this->min+1);
        }
        y=50+(this->scene()->height()-100)*(this->max-y)/(this->max-this->min);
        this->selectedXaxis=this->scene()->addLine(50,y,this->scene()->width()-50,y,pen);
        this->selectedYaxis=this->scene()->addLine(x,50,x,this->scene()->height()-50,pen);
        this->selectedItem=this->scene()->addRect(QRectF(-2.5,-2.5,5,5),QPen(Qt::darkBlue),QBrush(Qt::darkBlue));
        this->selectedItem->setPos(x,y);

        if(x<=this->scene()->width()/2&&y>=this->scene()->height()/2) {
            this->selectedIsotopeLabel=new SelectedIsotopeLabel(1,selectedName,selectedTextZ,selectedTextA,selectedValue,QColor(Qt::darkBlue));
            this->scene()->addItem(this->selectedIsotopeLabel);
            this->selectedIsotopeLabel->setPos(x,y-SelectedIsotopeLabel::shift());
        }else if(x>this->scene()->width()/2&&y>this->scene()->height()/2) {
            this->selectedIsotopeLabel=new SelectedIsotopeLabel(2,selectedName,selectedTextZ,selectedTextA,selectedValue,QColor(Qt::darkBlue));
            this->scene()->addItem(this->selectedIsotopeLabel);
            this->selectedIsotopeLabel->setPos(x-SelectedIsotopeLabel::shift(),y-SelectedIsotopeLabel::shift());
        }else if(x>this->scene()->width()/2&& y<this->scene()->height()/2) {
            this->selectedIsotopeLabel=new SelectedIsotopeLabel(3,selectedName,selectedTextZ,selectedTextA,selectedValue,QColor(Qt::darkBlue));
            this->scene()->addItem(this->selectedIsotopeLabel);
            this->selectedIsotopeLabel->setPos(x-SelectedIsotopeLabel::shift(),y);
        }else{
            this->selectedIsotopeLabel=new SelectedIsotopeLabel(4,selectedName,selectedTextZ,selectedTextA,selectedValue,QColor(Qt::darkBlue));
            this->scene()->addItem(this->selectedIsotopeLabel);
            this->selectedIsotopeLabel->setPos(x,y);
        }
    }
}

void IsotopesGraphView::resizeEvent(QResizeEvent* event)
{

    this->fitInView(this->scene()->itemsBoundingRect(),Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

void IsotopesGraphView::wheelEvent(QWheelEvent* event)
{
    event->ignore();
}

void IsotopesGraphView::updateIsotopes(int columnId)
{
    this->columnId=columnId;
    int rowCount=this->dataModel->rowCount();
    QPair<double,double> minmax=this->minMax(this->dataModel,rowCount,this->columnId);
    this->zero=0;
    if(this->columnId!=15)
    {
        this->max=minmax.second;
        this->min=minmax.first;
    }
    else
    {
        this->max=std::log10(minmax.second-minmax.first+1);
        this->min=0;
    }

    //dane izotopów
    QList<QGraphicsItem*> items=this->scene()->items(Qt::AscendingOrder);
    for(int i=0;i<rowCount;++i)
    {
        int z=this->dataModel->record(i).value(this->columnZid).toInt();
        QString value="";
        QGraphicsItem* item=items.at(i);
        if(!dataModel->record(i).value(this->columnId).isNull())
        {
            value=dataModel->record(i).value(this->columnId).toString();
            if(value=="Inf")
            {
                value="";
            }
            if(value!="")
            {
                double y=value.toDouble();
                if(this->columnId==15)
                {
                    y=std::log10(y-minmax.first+1);
                }
                item->setPos(50+z*this->factorX,50+(this->scene()->height()-100)*(this->max-y)/(this->max-this->min));
                item->setVisible(true);
            }
            else
            {
                item->setPos(50+z*this->factorX,this->scene()->height()-50);
                item->setVisible(false);
            }
        }
    }

    //uklad wspolrzednych
    this->minText->setPlainText(tr("%1").arg(minmax.first));
    this->maxText->setPlainText(tr("%1").arg(minmax.second));
    if(this->min*this->max<0)
    {
        this->zero=(this->scene()->height()-100)*this->max/(this->max-this->min);
    }
    else
    {
        this->zero=this->scene()->height()-100;
    }
    double mv=this->zero+37.5-(this->zeroText->y());
    this->zeroText->moveBy(0,mv);
    this->axisLine->moveBy(0,mv);
    this->labelXaxisText->moveBy(0,mv);

    //zaznaczenie
    this->generateSelected();

    this->scene()->update();

}

void IsotopesGraphView::updateSelected(int row)
{
    if(this->startIsotope!=row)
    {
        this->startIsotope=row;
        this->generateSelected();

        this->scene()->update();
    }
}

void IsotopesGraphView::changeGroupBy(int groupBy)
{
    switch (groupBy) {
    case 1:
        this->maxX=ISOBARES;
        this->columnZid=ISOB;
        this->factorX=(this->scene()->width()-100)/this->maxX;
        this->labelXaxisText->setPlainText("A");
        break;
    case 2:
        this->maxX=ISOTONES;
        this->columnZid=ISON;
        this->factorX=(this->scene()->width()-100)/this->maxX;
        this->labelXaxisText->setPlainText("N");
        break;
    default:
        this->maxX=ISOTOPES;
        this->columnZid=ISOT;
        this->factorX=(this->scene()->width()-100)/this->maxX;
        this->labelXaxisText->setPlainText("Z");
        break;
    }

    //uklad wspolrzednych
    QPen pen(Qt::DashLine);
    pen.setColor(Qt::lightGray);
    QGraphicsTextItem* textItem;
    QGraphicsLineItem* lineItem;
    while(!this->scaleOfX.isEmpty())
    {
        lineItem=this->scaleOfX.takeLast();
        this->scene()->removeItem(lineItem);
        delete lineItem;

    }
    while(!this->labelOfScaleX.isEmpty())
    {
        textItem=this->labelOfScaleX.takeLast();
        this->scene()->removeItem(textItem);
        delete textItem;
    }
    for(int i=10;i<this->maxX;i+=10)
    {
        lineItem=this->scene()->addLine(50+i*this->factorX,40,50+i*this->factorX,this->scene()->height()-40,pen);
        this->scaleOfX.append(lineItem);
        textItem=this->scene()->addText(tr("%1").arg(i));
        textItem->setPos(55+i*this->factorX,this->scene()->height()-50);
        this->labelOfScaleX.append(textItem);
        textItem=this->scene()->addText(tr("%1").arg(i));
        textItem->setPos(55+i*this->factorX,30);
        this->labelOfScaleX.append(textItem);
    }

    //dane izotopów
    int rowCount=this->dataModel->rowCount();
    QList<QGraphicsItem*> items=this->scene()->items(Qt::AscendingOrder);
    QGraphicsItem* item;
    for(int i=0;i<rowCount;++i)
    {
        int z=this->dataModel->record(i).value(this->columnZid).toInt();
        item=items.at(i);
        double mv=(50+z*this->factorX)-(item->x());
        item->moveBy(mv,0);
    }

    //zaznaczenie
    this->generateSelected();

    this->scene()->update();

}

QString IsotopesGraphView::getGraphName() const
{
    QString name;
    switch (this->columnId) {
    case 8:
        name="binding_energy";
        break;
    case 11:
        name="atomic_mass";
        break;
    case 15:
        name="half_life";
        break;
    case 20:
        name="beta_decay_energy";
        break;
    case 22:
        name="n_2_separation_energy";
        break;
    case 24:
        name="p_2_separation_energy";
        break;
    case 26:
        name="1_n_separation_energy";
        break;
    case 28:
        name="1_p_separation_energy";
        break;
    case 30:
        name="Q_alfa_energy";
        break;
    case 32:
        name="Q_2_beta_energy";
        break;
    case 34:
        name="Q_ep_energy";
        break;
    case 36:
        name="Q_beta_n_energy";
        break;
    case 38:
        name="Q_4_beta_energy";
        break;
    case 40:
        name="Q_da_energy";
        break;
    case 42:
        name="Q_pa_energy";
        break;
    case 44:
        name="Q_na_energy";
        break;
    default:
        name="mass_excess";
        break;
    }
    switch (this->columnZid) {
    case 2:
        name+="_by_isotones";
        break;
    case 3:
        name+="_by_isobares";
        break;
    default:
        name+="_by_isotopes";
        break;
    }
    return name;
}

void IsotopesGraphView::exportGraph()
{
    QString fileName="./"+this->getGraphName()+".png";
    fileName=QFileDialog::getSaveFileName(this,tr("Export Graph"),fileName,tr("Images (*.png)"));
    this->scene()->clearSelection();
    //bool isSelectedVisible=this->selectedItem->isVisible();
    if(this->selectedItem)
    {
        this->selectedItem->setVisible(false);
        this->selectedIsotopeLabel->setVisible(false);
        this->selectedXaxis->setVisible(false);
        this->selectedYaxis->setVisible(false);
    }
    QImage image(this->scene()->sceneRect().size().toSize(),QImage::Format_ARGB32);
    QPainter painter(&image);
    this->scene()->render(&painter);
    image.save(fileName);
    if(this->selectedItem)
    {
        this->selectedItem->setVisible(true);
        this->selectedIsotopeLabel->setVisible(true);
        this->selectedXaxis->setVisible(true);
        this->selectedYaxis->setVisible(true);
    }
}







