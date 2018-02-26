#ifndef ISOTOPEWIDGET_H
#define ISOTOPEWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLayoutItem>
#include <QFont>
#include <QGroupBox>
#include <QSqlRecord>
#include <QPainter>

class IsotopeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IsotopeWidget(int,QSqlQueryModel*,QWidget *parent = 0);

signals:
    void isotopeChanged(int);

public slots:
    void updateInfo(int);

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void previousButtonClicked();
    void nextButtonClicked();

private:
    QString getValue(int,int);
    QPushButton* previousButton;
    QPushButton* nextButton;
    QLabel* isotopeName;
    QLabel* z;
    QLabel* n;
    QLabel* a;
    QLabel* massExcess;
    QLabel* bindingEnergy;
    QLabel* atomicMass;
    QLabel* halfLife;
    QLabel* betaDecEnergy;
    QLabel* energyS2n;
    QLabel* energyS2p;
    QLabel* energySn;
    QLabel* energySp;
    QLabel* qAlfa;
    QLabel* q2b;
    QLabel* qep;
    QLabel* qbn;
    QLabel* q4b;
    QLabel* qda;
    QLabel* qpa;
    QLabel* qna;
    QSqlQueryModel* dataModel;
    const int maxRow;
    int actualRow;

};

#endif // ISOTOPEWIDGET_H
