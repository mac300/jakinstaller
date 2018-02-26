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
    QList<QAction*> actions=dynamic_cast<MainWindow*>(this->parent())->getIsotopeActions();
    foreach (QAction* action,actions)
    {
        if(action!=this)
        {
            action->setEnabled(true);
            action->setChecked(false);
        }
        else
        {
            action->setEnabled(false);
            action->setChecked(true);
        }
    }
    emit actionSelected(this->columnKind);
}
