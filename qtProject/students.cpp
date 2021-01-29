#include "students.h"

Students::Students(QObject *parent) : QObject(parent)
{

}

void Students::setNames(QString name)
{
    names.append(name);
}

void Students::setMarks(float mark)
{
    marks.append(mark);
}

void Students::clearReg()
{
    marks.clear();
    names.clear();
}

QStringList Students::getNames()
{
    return names;
}

QList<float> Students::getMarks()
{
   return marks;
}
