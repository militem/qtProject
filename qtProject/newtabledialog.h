#ifndef NEWTABLEDIALOG_H
#define NEWTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class NewTableDialog;
}

class QSpinBox;

class NewTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTableDialog(QWidget *parent = nullptr);
    ~NewTableDialog();
    int getRowsCount() const;
    int getColsCount() const;

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void configureSpinBox(QSpinBox *spinBox, int min, int max) const;
    Ui::NewTableDialog *ui;

};

#endif // NEWTABLEDIALOG_H
