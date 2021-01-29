#ifndef PILA_H
#define PILA_H

#include <QObject>

class Pila : public QObject
{
    Q_OBJECT
public:
    explicit Pila(QObject *parent = nullptr);
    Pila(QStringList, QList<int>, QList<int>);
    QStringList getData();
    QList<int> getColumn();
    QList<int> getRow();
    void clearReg();

signals:

private:
    QStringList data;
    QList<int> row, column;
};

#endif // PILA_H
