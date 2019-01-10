#include "isotopeaction.h"

IsotopeAction::IsotopeAction(IsotopeAction::Kind kind,QString text,QObject* parent) :
    QAction(text,parent)
{
    this->setCheckable(true);
    this->setChecked(false);
    this->columnKind=kind;

    connect(this,SIGNAL(triggered()),this,SLOT(actionSelect()));
}

void IsotopeAction::actionSelect()
{
    emit actionSelected(this);
    emit actionSelected(this->columnKind);
}
