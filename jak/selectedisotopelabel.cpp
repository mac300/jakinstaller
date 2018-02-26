#include "selectedisotopelabel.h"

SelectedIsotopeLabel::SelectedIsotopeLabel(int t,QString smb,QString z,QString a,QString v,QColor c)
    :labelType(t),smb(smb),z(z),a(a),value(v),color(c){}

QRectF SelectedIsotopeLabel::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void SelectedIsotopeLabel::paint(QPainter* painter,const QStyleOptionGraphicsItem*,QWidget*)
{
    painter->setPen(this->color);
    QFont font(qApp->font());
    font.setBold(true);
    painter->setFont(font);
    QColor backColor(Qt::white);
    backColor.setAlpha(175);
    QFontMetricsF metrics(font);
    QRectF rect;
    QString text;
    double dy;
    switch (this->labelType)
    {
    case 2:
        painter->fillRect(0,115,175,60,QBrush(backColor));
        painter->drawRect(0,115,175,60);
        painter->setPen(Qt::darkGray);
        painter->drawLine(2,177,177,177);
        painter->drawLine(177,115,177,177);
        painter->setPen(this->color);
        painter->drawLine(175,175,200,200);

        text="value = "+this->value;
        rect==metrics.boundingRect(text);
        dy=rect.height();
        painter->drawText(10,165-dy,text);
        text="Z = "+this->z+" , A = "+this->a;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(10,165-dy,text);
        text=this->smb;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(10,165-dy,text);

        break;
    case 3:
        painter->fillRect(0,25,175,60,QBrush(backColor));
        painter->drawRect(0,25,175,60);
        painter->setPen(Qt::darkGray);
        painter->drawLine(2,87,177,87);
        painter->drawLine(177,25,177,87);
        painter->setPen(this->color);
        painter->drawLine(175,25,200,0);

        text="value = "+this->value;
        rect==metrics.boundingRect(text);
        dy=rect.height();
        painter->drawText(10,75-dy,text);
        text="Z = "+this->z+" , A = "+this->a;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(10,75-dy,text);
        text=this->smb;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(10,75-dy,text);

        break;
    case 4:
        painter->fillRect(25,25,175,60,QBrush(backColor));
        painter->drawRect(25,25,175,60);
        painter->setPen(Qt::darkGray);
        painter->drawLine(27,87,202,87);
        painter->drawLine(202,25,202,87);
        painter->setPen(this->color);
        painter->drawLine(0,0,25,25);

        text="value = "+this->value;
        rect==metrics.boundingRect(text);
        dy=rect.height();
        painter->drawText(35,75-dy,text);
        text="Z = "+this->z+" , A = "+this->a;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(35,75-dy,text);
        text=this->smb;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(35,75-dy,text);

        break;
    default:
        painter->fillRect(25,115,175,60,QBrush(backColor));
        painter->drawRect(25,115,175,60);
        painter->setPen(Qt::darkGray);
        painter->drawLine(27,177,202,177);
        painter->drawLine(202,115,202,177);
        painter->setPen(this->color);
        painter->drawLine(0,200,25,175);

        text="value = "+this->value;
        rect==metrics.boundingRect(text);
        dy=rect.height();
        painter->drawText(35,165-dy,text);
        text="Z = "+this->z+" , A = "+this->a;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(35,165-dy,text);
        text=this->smb;
        rect=metrics.boundingRect(text);
        dy+=rect.height();
        painter->drawText(35,165-dy,text);

        break;
    }
}

double SelectedIsotopeLabel::shift()
{
    return 200.0;
}
