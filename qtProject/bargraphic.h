#ifndef BARGRAPHIC_H
#define BARGRAPHIC_H

#include <QObject>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

class QChart;

class BarGraphic : public QObject
{
    Q_OBJECT
public:
    explicit BarGraphic(QObject *parent = nullptr);
    BarGraphic(QStringList, QList<float>);
    QChart *getGraphic() const;

signals:

private:
    QStringList names;
    QList<float> marks;
};

#endif // BARGRAPHIC_H
