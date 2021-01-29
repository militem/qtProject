#include "bargraphic.h"

BarGraphic::BarGraphic(QObject *parent) : QObject(parent)
{

}

BarGraphic::BarGraphic(QStringList _names, QList<float> _marks)
{
    names = _names;
    marks = _marks;
}

QChart *BarGraphic::getGraphic() const
{
    QBarSeries *series = new QBarSeries();
    for(int i = 0; i < marks.count(); i++){
        QBarSet *set = new QBarSet("");
        if(marks[i] >= 70){
            set->setLabel(names[i] + " Aprobado");
            set->setLabelColor(Qt::green);
            set->setBorderColor(Qt::darkGray);
            set->append(marks[i]);
        }else{
            set->setLabel(names[i] + " Reprobado");
            set->setLabelColor(Qt::red);
            set->setBorderColor(Qt::darkGray);
            set->append(marks[i]);
        }
        series->append(set);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Notas";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return chart;
}
