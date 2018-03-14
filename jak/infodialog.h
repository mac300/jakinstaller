#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QString>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QString, QString, QString , QIcon, QWidget *parent = 0);
    ~InfoDialog();

private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
