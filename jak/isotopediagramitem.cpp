#include "isotopediagramitem.h"
#include <QApplication>
#include <QFont>
#include <QPoint>
#include <QPen>
#include <QLinearGradient>
#include <cmath>
#include <QFontMetricsF>
#include <cmath>

IsotopeDiagramItem::IsotopeDiagramItem(int ind,int z,int n,QString smb,QString value)
{
    this->index=ind;
    this->z=z;
    this->n=n;
    this->smb=smb;
    this->value=value;
    this->generateColor();
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

double IsotopeDiagramItem::minValue=0;
double IsotopeDiagramItem::maxValue=1;
QString IsotopeDiagramItem::valueLabel="";

int IsotopeDiagramItem::getZ() const
{
    return this->z;
}

int IsotopeDiagramItem::getN() const
{
    return this->n;
}

int IsotopeDiagramItem::getIndex() const
{
    return this->index;
}

QString IsotopeDiagramItem::getValue() const
{
    return this->value;
}

void IsotopeDiagramItem::setValue(const QString value)
{
    this->value=value;
    this->generateColor();
}

void IsotopeDiagramItem::setIsotopeDiagramItem(const double min, const double max, const QString label)
{
    IsotopeDiagramItem::minValue=min;
    IsotopeDiagramItem::maxValue=max;
    IsotopeDiagramItem::valueLabel=label+":";
}

QPointF IsotopeDiagramItem::shift(QPointF point)
{
    point.setX(point.x()+25);
    point.setY(point.y()+25);
    return point;
}

void IsotopeDiagramItem::generateColor()
{
    if(this->value=="")
    {
        this->color=QColor(Qt::white);
    }
    else if(this->value=="Inf")
    {
        this->color=QColor(100,100,100);
    }
    else
    {
        double hValue=this->value.toDouble();
        int h;
        if(IsotopeDiagramItem::valueLabel=="Half Life:")
        {
            double max=std::log10(IsotopeDiagramItem::maxValue-IsotopeDiagramItem::minValue+1);
            hValue=std::log10(hValue-IsotopeDiagramItem::minValue+1);
            h=std::floor(300.0*(hValue)/(max));
        }
        else
        {
            h=std::floor(300.0*(hValue-IsotopeDiagramItem::minValue)/(IsotopeDiagramItem::maxValue-IsotopeDiagramItem::minValue));
        }
        QColor color;
        color.setHsv(h,255,255);
        this->color=color;
    }
}

QRectF IsotopeDiagramItem::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void IsotopeDiagramItem::paint(QPainter* painter,const QStyleOptionGraphicsItem* /*option*/,QWidget* /*widget*/)
{
    if(this->value=="Inf")
    {
        painter->setPen(QColor(Qt::white));
    }
    else
    {
        painter->setPen(QColor(Qt::black));
    }
    QRectF rect=this->boundingRect();
    double levelOfDetail=QStyleOptionGraphicsItem::levelOfDetailFromTransform(painter->worldTransform());
    if(levelOfDetail<.8)
    {
        painter->fillRect(rect,this->color);
        painter->drawRect(QRectF(2,2,46,46));
    }
    else
    {
        QLinearGradient gradient(QPoint(0,0),QPoint(50,50));
        gradient.setColorAt(0.0,this->color.lighter(130));
        gradient.setColorAt(1.0,this->color.darker(130));
        painter->fillRect(rect,gradient);
        painter->drawRect(QRectF(2,2,46,46));
        painter->drawLine(5,35,45,35);

        QFont font = qApp->font();
        font.setPixelSize(8);
        painter->setFont(font);
        QFontMetricsF metrics(font);
        QRectF rect=metrics.boundingRect(tr("%1").arg((this->z)+(this->n)));
        painter->drawText(17-rect.width(),15,tr("%1").arg((this->z)+(this->n)));
        rect=metrics.boundingRect(tr("%1").arg(this->z));
        painter->drawText(17-rect.width(),30,tr("%1").arg(this->z));

        font.setPixelSize(15);
        painter->setFont(font);
        painter->drawText(19,25,this->smb);

        font.setPixelSize(4);
        painter->setFont(font);
        painter->drawText(5,40,IsotopeDiagramItem::valueLabel);
        if(this->value=="")
        {
            painter->drawText(5,45,"inaccessible");
        }
        else
        {
            painter->drawText(5,45,this->value);
        }
    }
    if(this->isSelected())
    {
        QColor color(Qt::black);
        if(this->color!=QColor(Qt::white))
        {
            int hue=this->color.hslHue();
            if(hue<30||hue>200)
            {
                color=QColor(Qt::white);
            }
        }
        painter->setPen(color);
        painter->drawRect(QRectF(1,1,48,48));
        color.setAlpha(100);
        painter->fillRect(QRectF(1,1,48,48),color);
    }
}





