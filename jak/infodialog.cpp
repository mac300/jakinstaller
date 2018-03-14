#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QString title, QString fileName, QString pngName, QIcon icon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->setWindowIcon(icon);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    QPixmap logo(pngName);
    ui->logoLabel->setPixmap(logo);
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        ui->textBrowser->setText(QString::fromUtf8(QTextStream(&file).readAll().toLocal8Bit()));
        file.close();
    }
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
