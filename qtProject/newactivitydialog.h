#ifndef NEWACTIVITYDIALOG_H
#define NEWACTIVITYDIALOG_H

#include <QDialog>

namespace Ui {
class NewActivityDialog;
}

class NewActivityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewActivityDialog(QWidget *parent = nullptr);
    ~NewActivityDialog();
    QString getNameActivity();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewActivityDialog *ui;
};

#endif // NEWACTIVITYDIALOG_H
