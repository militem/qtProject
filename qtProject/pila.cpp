#include "pila.h"

Pila::Pila(QObject *parent) : QObject(parent)
{
    data.append("");
}

Pila::Pila(QStringList _data, QList<int> _row, QList<int> _column)
{
    data.append(_data);
    row.append(_row);
    column.append(_column);
}

QStringList Pila::getData(){
    return data;
}

QList<int> Pila::getColumn()
{
    return column;
}

QList<int> Pila::getRow()
{
    return row;
}

void Pila::clearReg()
{
    data.clear();
    column.clear();
    row.clear();
}
