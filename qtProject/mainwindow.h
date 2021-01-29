#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <students.h>
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QtGui>
#include <QtCore>
#include <QBrush>
#include <QStack>
#include "pila.h"

struct nodo{
     float nro;
     struct nodo *izq, *der;
 };

typedef struct nodo *ABB;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Metodos para crear arbol binario
    ABB crearNodo(int x);
    void insertar(ABB &arbol, int x);
    void enOrden(ABB arbol);
    void verArbol(ABB arbol, int n);
    void inicio();
    void esfera(int radio, int x, int y,int incrementox, int incrementoy, QString texto,QColor colorfondo,QColor colorlinea);
    float n;
    float x;
    ABB arbol = NULL;

private slots:
    void on_actionSave_triggered();

    void on_actionNew_triggered();

    void on_actionCreateBarGraphic_triggered();

    void on_actionOpen_triggered();

    void on_actionAddActivity_triggered();

    void on_actionRemoveActivity_triggered();

    void on_actionAddStudent_triggered();

    void on_actionRemoveStudent_triggered();

    void on_actionCalculate_Average_triggered();

    void on_actionSave_Graphic_triggered();

    void on_actionPrint_triggered();

    void on_actionCreated_Binary_Tree_triggered();   

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:

    QString getValueAt(int, int) const;
    void setValueAt(int, int, const QString &value);
    void createBars(QList<float>, QStringList);
    QChartView* chartView;
    Ui::MainWindow *ui;
    QStandardItemModel *mModel;
    Students *std = new Students();
    QStack<Pila*> pila;
    Pila *p;
    int countPila = 0, countRedo = 1, countUndo = 1;

    //arbol binario
    QPixmap pixmap;
    QLabel *tree = new QLabel("");
    int radio = 30;
    int x1 = 0;
    int y1 = 20;
    int incrementox = 0;
    int incrementoy = 0;
    int countNodo = 0;
};
#endif // MAINWINDOW_H
