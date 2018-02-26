#ifndef ISOTOPEACTION_H
#define ISOTOPEACTION_H

#include "mainwindow.h"
#include <QAction>
#include <QString>
#include <QList>
#include <iostream>

class IsotopeAction : public QAction
{
    Q_OBJECT

public:
    enum Kind
    {
        MASS_EXCESS=6,
        BINDING_ENERGY=8,
        ATOMIC_MASS=11,
        HALF_LIFE=15,
        BETA_DECAY_ENERGY=20,
        N2_SEPARATION=22,
        P2_SEPARATION=24,
        N_SEPARATION=26,
        P_SEPARATION=28,
        Q_A=30,
        Q_2B=32,
        Q_EP=34,
        Q_BN=36,
        Q_4B=38,
        Q_DA=40,
        Q_PA=42,
        Q_NA=44
    };

    explicit IsotopeAction(IsotopeAction::Kind,QString,QObject* = 0);

signals:
    void actionSelected(const int);

private slots:
    void actionSelect();

private:
    int columnKind;

};

#endif // ISOTOPEACTION_H
