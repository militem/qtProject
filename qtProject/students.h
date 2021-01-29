#ifndef STUDENTS_H
#define STUDENTS_H

#include <QObject>

class Students : public QObject
{
    Q_OBJECT
public:
    explicit Students(QObject *parent = nullptr);
    void setNames(QString);
    void setMarks(float);
    void clearReg();
    QStringList getNames();
    QList<float> getMarks();

signals:

private:
    QStringList names;
    QList<float> marks;
};

#endif // STUDENTS_H
