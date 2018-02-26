#include "isotopewidget.h"

IsotopeWidget::IsotopeWidget(int startRow,QSqlQueryModel* model,QWidget *parent)
    :QWidget(parent),maxRow(model->rowCount()-1)
{
    this->dataModel=model;
    this->actualRow=startRow;

    //layouts
    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    QVBoxLayout* topLayout=new QVBoxLayout;
    QVBoxLayout* leftLayout=new QVBoxLayout;
    QVBoxLayout* rightLayout=new QVBoxLayout;
    QHBoxLayout* buttomLayout=new QHBoxLayout;
    QHBoxLayout* layout01=new QHBoxLayout;
    QHBoxLayout* layout02=new QHBoxLayout;
    QHBoxLayout* layout03=new QHBoxLayout;
    QHBoxLayout* layout04=new QHBoxLayout;
    QHBoxLayout* layout05=new QHBoxLayout;
    QHBoxLayout* layout06=new QHBoxLayout;
    QHBoxLayout* layout07=new QHBoxLayout;
    QHBoxLayout* layout08=new QHBoxLayout;
    QHBoxLayout* layout09=new QHBoxLayout;
    QHBoxLayout* layout10=new QHBoxLayout;
    QHBoxLayout* layout11=new QHBoxLayout;
    QHBoxLayout* layout12=new QHBoxLayout;
    QHBoxLayout* layout13=new QHBoxLayout;
    QHBoxLayout* layout14=new QHBoxLayout;
    QHBoxLayout* layout15=new QHBoxLayout;
    QHBoxLayout* layout16=new QHBoxLayout;
    QHBoxLayout* layout17=new QHBoxLayout;
    QHBoxLayout* layout18=new QHBoxLayout;
    QHBoxLayout* layout19=new QHBoxLayout;

    topLayout->addLayout(layout01);
    topLayout->addSpacing(10);
    topLayout->addLayout(layout02);

    leftLayout->addSpacing(5);
    leftLayout->addLayout(layout03);
    leftLayout->addLayout(layout04);
    leftLayout->addLayout(layout05);
    leftLayout->addLayout(layout06);
    leftLayout->addLayout(layout07);
    leftLayout->addLayout(layout08);
    leftLayout->addLayout(layout09);
    leftLayout->addLayout(layout10);
    leftLayout->addLayout(layout11);
    leftLayout->addStretch();
    rightLayout->addSpacing(5);
    rightLayout->addLayout(layout12);
    rightLayout->addLayout(layout13);
    rightLayout->addLayout(layout14);
    rightLayout->addLayout(layout15);
    rightLayout->addLayout(layout16);
    rightLayout->addLayout(layout17);
    rightLayout->addLayout(layout18);
    rightLayout->addLayout(layout19);
    rightLayout->addStretch();

    buttomLayout->addStretch();
    buttomLayout->addLayout(leftLayout);
    buttomLayout->addStretch();
    buttomLayout->addLayout(rightLayout);
    buttomLayout->addStretch();

    QGroupBox* topGroup=new QGroupBox;
    topGroup->setLayout(topLayout);
    QGroupBox* buttomGroup=new QGroupBox;
    buttomGroup->setLayout(buttomLayout);
    mainLayout->addWidget(topGroup);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttomGroup);


    //content
    this->previousButton=new QPushButton(QIcon(tr(":/icons/left.png")),"");
    this->nextButton=new QPushButton(QIcon(tr(":/icons/right.png")),"");
    this->isotopeName=new QLabel(this->getValue(this->actualRow,46));
    this->isotopeName->setAlignment(Qt::AlignCenter);
    QFont largeFont,midiumFont,boldFont;
    boldFont=this->isotopeName->font();
    boldFont.setWeight(QFont::Bold);
    midiumFont=largeFont=boldFont;
    midiumFont.setPointSize(midiumFont.pointSize()+4);
    largeFont.setPointSize(largeFont.pointSize()+10);
    this->isotopeName->setFont(largeFont);
    layout01->addWidget(this->previousButton);
    layout01->addStretch();
    layout01->addWidget(this->isotopeName);
    layout01->addStretch();
    layout01->addWidget(this->nextButton);

    this->z=new QLabel(this->getValue(this->actualRow,1));
    this->z->setFont(midiumFont);
    this->n=new QLabel(this->getValue(this->actualRow,2));
    this->n->setFont(midiumFont);
    this->a=new QLabel(this->getValue(this->actualRow,3));
    this->a->setFont(midiumFont);
    QLabel* zLabel=new QLabel("Z: ");
    zLabel->setFont(midiumFont);
    QLabel* nLabel=new QLabel("N: ");
    nLabel->setFont(midiumFont);
    QLabel* aLabel=new QLabel("A: ");
    aLabel->setFont(midiumFont);
    layout02->addStretch();
    layout02->addWidget(zLabel);
    layout02->addWidget(this->z);
    layout02->addStretch();
    layout02->addWidget(nLabel);
    layout02->addWidget(this->n);
    layout02->addStretch();
    layout02->addWidget(aLabel);
    layout02->addWidget(this->a);
    layout02->addStretch();

    this->massExcess=new QLabel(this->getValue(this->actualRow,6));
    this->bindingEnergy=new QLabel(this->getValue(this->actualRow,8));
    QLabel* label=new QLabel("mass excess: ");
    label->setFont(boldFont);
    layout03->addWidget(label);
    layout03->addStretch();
    layout03->addWidget(this->massExcess);
    label=new QLabel("binding energy: ");
    label->setFont(boldFont);
    layout04->addWidget(label);
    layout04->addStretch();
    layout04->addWidget(this->bindingEnergy);
    this->atomicMass=new QLabel(this->getValue(this->actualRow,11));
    this->halfLife=new QLabel(this->getValue(this->actualRow,15));
    label=new QLabel("atomic mass: ");
    label->setFont(boldFont);
    layout05->addWidget(label);
    layout05->addStretch();
    layout05->addWidget(this->atomicMass);
    label=new QLabel("half life: ");
    label->setFont(boldFont);
    layout06->addWidget(label);
    layout06->addStretch();
    layout06->addWidget(this->halfLife);
    this->betaDecEnergy=new QLabel(this->getValue(this->actualRow,20));
    this->energyS2n=new QLabel(this->getValue(this->actualRow,22));
    label=new QLabel("\u03b2 decay energy: ");
    label->setFont(boldFont);
    layout07->addWidget(label);
    layout07->addStretch();
    layout07->addWidget(this->betaDecEnergy);
    label=new QLabel("S 2n energy: ");
    label->setFont(boldFont);
    layout08->addWidget(label);
    layout08->addStretch();
    layout08->addWidget(this->energyS2n);
    this->energyS2p=new QLabel(this->getValue(this->actualRow,24));
    this->energySn=new QLabel(this->getValue(this->actualRow,26));
    label=new QLabel("S 2p energy: ");
    label->setFont(boldFont);
    layout09->addWidget(label);
    layout09->addStretch();
    layout09->addWidget(this->energyS2p);
    label=new QLabel("S 1n energy: ");
    label->setFont(boldFont);
    layout10->addWidget(label);
    layout10->addStretch();
    layout10->addWidget(this->energySn);
    this->energySp=new QLabel(this->getValue(this->actualRow,28));
    this->qAlfa=new QLabel(this->getValue(this->actualRow,30));
    label=new QLabel("S 1p energy: ");
    label->setFont(boldFont);
    layout11->addWidget(label);
    layout11->addStretch();
    layout11->addWidget(this->energySp);
    label=new QLabel("Q \u03b1 energy: ");
    label->setFont(boldFont);
    layout12->addWidget(label);
    layout12->addStretch();
    layout12->addWidget(this->qAlfa);
    this->q2b=new QLabel(this->getValue(this->actualRow,32));
    this->qep=new QLabel(this->getValue(this->actualRow,34));
    label=new QLabel("Q 2\u03b2 energy: ");
    label->setFont(boldFont);
    layout13->addWidget(label);
    layout13->addStretch();
    layout13->addWidget(this->q2b);
    label=new QLabel("Q ep energy: ");
    label->setFont(boldFont);
    layout14->addWidget(label);
    layout14->addStretch();
    layout14->addWidget(this->qep);
    this->qbn=new QLabel(this->getValue(this->actualRow,36));
    this->q4b=new QLabel(this->getValue(this->actualRow,38));
    label=new QLabel("Q \u03b2n energy: ");
    label->setFont(boldFont);
    layout15->addWidget(label);
    layout15->addStretch();
    layout15->addWidget(this->qbn);
    label=new QLabel("Q 4\u03b2 energy: ");
    label->setFont(boldFont);
    layout16->addWidget(label);
    layout16->addStretch();
    layout16->addWidget(this->q4b);
    this->qda=new QLabel(this->getValue(this->actualRow,40));
    this->qpa=new QLabel(this->getValue(this->actualRow,42));
    label=new QLabel("Q d\u03b1 energy: ");
    label->setFont(boldFont);
    layout17->addWidget(label);
    layout17->addStretch();
    layout17->addWidget(this->qda);
    label=new QLabel("Q p\u03b1 energy: ");
    label->setFont(boldFont);
    layout18->addWidget(label);
    layout18->addStretch();
    layout18->addWidget(this->qpa);
    this->qna=new QLabel(this->getValue(this->actualRow,44));
    label=new QLabel("Q n\u03b1 energy: ");
    label->setFont(boldFont);
    layout19->addWidget(label);
    layout19->addStretch();
    layout19->addWidget(this->qna);

    this->setAutoFillBackground(true);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window,Qt::white);
    palette.setColor(QPalette::WindowText,Qt::darkGray);
    this->setPalette(palette);

    connect(this->previousButton,SIGNAL(clicked()),this,SLOT(previousButtonClicked()));
    connect(this->nextButton,SIGNAL(clicked()),this,SLOT(nextButtonClicked()));

}

QString IsotopeWidget::getValue(int record, int column)
{
    QString data="";
    QString excess="";
    if(!this->dataModel->record(record).value(column).isNull())
    {
        data=this->dataModel->record(record).value(column).toString();
    }
    if(data=="")
    {
        return QString("inaccessible");
    }
    if(column<4||column==46)
    {
        return data;
    }
    if(!this->dataModel->record(record).value(column+1).isNull())
    {
        excess=this->dataModel->record(record).value(column+1).toString();
    }
    if(excess=="")
    {
        return data;
    }
    else
    {
        return data+" \u00b1 "+excess;
    }
}

void IsotopeWidget::updateInfo(int row)
{
    if(row!=this->actualRow)
    {
        this->actualRow=row;
        this->previousButton->setEnabled(this->actualRow);
        this->nextButton->setEnabled(this->maxRow-this->actualRow);
        this->isotopeName->setText(this->getValue(row,46));
        this->z->setText(this->getValue(row,1));
        this->n->setText(this->getValue(row,2));
        this->a->setText(this->getValue(row,3));
        this->massExcess->setText(this->getValue(row,6));
        this->bindingEnergy->setText(this->getValue(row,8));
        this->atomicMass->setText(this->getValue(row,11));
        this->halfLife->setText(this->getValue(row,15));
        this->betaDecEnergy->setText(this->getValue(row,20));
        this->energyS2n->setText(this->getValue(row,22));
        this->energyS2p->setText(this->getValue(row,24));
        this->energySn->setText(this->getValue(row,26));
        this->energySp->setText(this->getValue(row,28));
        this->qAlfa->setText(this->getValue(row,30));
        this->q2b->setText(this->getValue(row,32));
        this->qep->setText(this->getValue(row,34));
        this->qbn->setText(this->getValue(row,36));
        this->q4b->setText(this->getValue(row,38));
        this->qda->setText(this->getValue(row,40));
        this->qpa->setText(this->getValue(row,42));
        this->qna->setText(this->getValue(row,44));
    }
}

void IsotopeWidget::previousButtonClicked()
{
    if(!this->nextButton->isEnabled())
    {
        this->nextButton->setEnabled(true);
    }
    this->updateInfo(this->actualRow-1);
    if(!this->actualRow)
    {
        this->previousButton->setEnabled(false);
    }
    emit this->isotopeChanged(this->actualRow);
}

void IsotopeWidget::nextButtonClicked()
{
    if(!this->previousButton->isEnabled())
    {
        this->previousButton->setEnabled(true);
    }
    this->updateInfo(this->actualRow+1);
    if(this->actualRow==this->maxRow)
    {
        this->nextButton->setEnabled(false);
    }
    emit this->isotopeChanged(this->actualRow);
}

void IsotopeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect rect=this->contentsRect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRect(rect);
    QWidget::paintEvent(event);
}







