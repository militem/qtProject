#include "mainwindow.h"
#include "ui_mainwindow.h"
/* Librerias propias */
#include "newtabledialog.h"
#include "newactivitydialog.h"
#include "students.h"
/* ----------------- */
#include <QStandardItem>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPixmap>
#include <QPainter>
#include <QPen>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mModel = new QStandardItemModel(this);
    ui->tableView->setModel(mModel);
    setValueAt(0, 0, "Apellidos");
    setValueAt(0, 1, "Nombres");
    setValueAt(0, 2, "Nota Final");
    //Deshabilitar la columana del promedio.
    createBars(std->getMarks(), std->getNames());
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBars(QList<float> marks, QStringList names){
    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart* chart = chartView->chart();
    QBarSeries *series = new QBarSeries();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
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

    chart->addSeries(series);
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Titulo");

    axisX->append("Notas");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->gridLayout_3->addWidget(chartView, 0, 0);
}

void MainWindow::on_actionSave_Graphic_triggered()
{
    QPixmap pixmap = chartView->grab();

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,"Guardar",QString(),"Imagen(*.png)");
    if(!fileName.isEmpty()){
        if (pixmap.save(fileName)){
            QMessageBox::information(this,"Guardado","Archivo almacenada "+fileName);
        }else{
            QMessageBox::warning(this,"Error", "No pudo guaradar");
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Guardar", QDir::rootPath(), "CSV File (*.csv)");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream xout(&file);
    const int rowCount = mModel->rowCount();
    const int colCount = mModel->columnCount();
    for (int ix = 0; ix < rowCount; ++ix) {
        xout << getValueAt(ix, 0);
        for (int jx = 1; jx < colCount; ++jx) {
            xout << ", " << getValueAt(ix, jx);
        }
        xout << "\n";
    }
    file.flush();
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    NewTableDialog d(this);
    if(d.exec() == QDialog::Rejected){
        return;
    }
    const int rowCount = d.getRowsCount();
    const int colCount = d.getColsCount();
    mModel->clear();
    std->clearReg();
    createBars(std->getMarks(), std->getNames());
    mModel->setRowCount(rowCount + 1);
    mModel->setColumnCount(colCount + 3);
    setValueAt(0, 0, "Apellidos");
    setValueAt(0, 1, "Nombres");
    setValueAt(0, 2, "Nota Final");
}

void MainWindow::on_actionAddActivity_triggered()
{
    setValueAt(0, 0, "Apellidos");
    setValueAt(0, 1, "Nombres");
    setValueAt(0, 2, "Nota Final");
    mModel->setColumnCount(mModel->columnCount() + 1);
}

void MainWindow::on_actionRemoveActivity_triggered()
{
    mModel->removeColumn(mModel->columnCount() - 1);
}

void MainWindow::on_actionAddStudent_triggered()
{
    mModel->setRowCount(mModel->rowCount() + 1);
}
void MainWindow::on_actionRemoveStudent_triggered()
{
    mModel->removeRow(mModel->rowCount() - 1);
}

void MainWindow::on_actionCalculate_Average_triggered()
{
    float acum = 0, general = 0;
    for(int j = 1; j < mModel->rowCount(); j++){
       acum = 0;
       for(int i = 3; i < mModel->columnCount(); i++) {
           if(getValueAt(j, i).toFloat() != NULL && getValueAt(j, i).toFloat() <= 50){
               acum += getValueAt(j, i).toFloat();
           }else{
               setValueAt(j, i, "0");
               QMessageBox::information(this, tr("Error ingreso de notas"), tr("Ingreso de caracter no valido, se dejo una celda vacia o un numero mayor a 50. Se ingresara un 0."));
           }
       }
       if(acum <= 100){
            setValueAt(j, 2, QString::number(acum));
            general += acum;
       }else{
            QMessageBox::information(this, tr("Error suma de notas"), tr("La suma de notas es mayor a 100. Revise las notas ingresadas."));
       }
    }
    general /= (mModel->rowCount() - 1);
    setValueAt(mModel->rowCount(), 2, QString::number(general));
    //Pila
    QStringList data;
    QList<int> row, column;
    for(int j = 0; j < mModel->rowCount(); j++){
        for(int i = 0; i < mModel->columnCount(); i++){
            data.append(getValueAt(j, i));
            row.append(j);
            column.append(i);
            //pila.push(new Pila(getValueAt(j, i), j, i));
        }
    }
    pila.push(new Pila(data, row, column));
    /*for(int i = 0; i <= countPila; i++){
        p = pila.at(i);
        qDebug()<<p->getData();
        qDebug()<<p->getRow();
        qDebug()<<p->getColumn();
    }
    qDebug()<<countPila;*/
    countPila++;
}

void MainWindow::on_actionUndo_triggered()
{
    if((countPila - 1) - countUndo < 0){
        return;
    }
    mModel->clear();
    std->clearReg();
    p = pila.at((countPila - 1) - countUndo);
    for(int j = 0; j < p->getData().count(); j++){
        setValueAt(p->getRow().at(j), p->getColumn().at(j), p->getData().at(j));
    }
    countRedo = (countPila - 1) - countUndo;
    countUndo++;
}

void MainWindow::on_actionRedo_triggered()
{
    if(countRedo + 1 >= countPila){
        return;
    }
    mModel->clear();
    std->clearReg();
    p = pila.at(countRedo + 1);
    for(int j = 0; j < p->getData().count(); j++){
        setValueAt(p->getRow().at(j), p->getColumn().at(j), p->getData().at(j));
    }
    countRedo++;
}

QString MainWindow::getValueAt(int ix, int jx) const{
    if(!mModel->item(ix, jx)){
        return "";
    }
    return mModel->item(ix, jx)->text();
}

void MainWindow::setValueAt(int ix, int jx, const QString &value){
    if(!mModel->item(ix, jx)){
        mModel->setItem(ix, jx, new QStandardItem(value));
    }else{
        mModel->item(ix, jx)->setText(value);
    }
}

void MainWindow::on_actionCreateBarGraphic_triggered()
{
    std->clearReg();
    for(int j = 1; j < mModel->rowCount(); j++){
        std->setNames(getValueAt(j, 0) + " " + getValueAt(j, 1));
    }
    for(int j = 1; j < mModel->rowCount(); j++){
        std->setMarks(getValueAt(j, 2).toFloat());
    }
    createBars(std->getMarks(), std->getNames());
}

void MainWindow::on_actionOpen_triggered()
{
    auto filename = QFileDialog::getOpenFileName(this, "Abrir", QDir::rootPath(), "CSV File (*.csv)");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream xin(&file);
    int ix = 0;
    while (!xin.atEnd()) {
        auto line = xin.readLine();
        auto elements = line.split(",");
        const int elementsSize = elements.size();
        mModel->setRowCount(ix + 1);
        mModel->setColumnCount(elementsSize);
        for (int jx = 0; jx < elementsSize; ++jx) {
            setValueAt(ix, jx, elements.at(jx));
        }
        ++ix;
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPixmap pixmap = chartView->grab();

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,"Guardar Imagen",QString(),"Imagen(*.png)");
    if(!fileName.isEmpty()){
        if (!pixmap.save(fileName)){
            QMessageBox::warning(this,"Error", "No pudo guaradar");
        }
    }
    QString strStream, strTitle = "Reporte Completo de Notas";
    QTextStream out(&strStream);
    const int rowCount = mModel->rowCount();
    const int colCount = mModel->columnCount();
    out<<"<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<QString("<title>%1</title>\n").arg(strTitle)
            <<"</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<p><center><h1>Titulo por defecto</h1></center></p>"
            "<p><table border=1 cellspacing=1 cellpadding=3>\n";
    out<<"<thead><tr bgcolor=#f0f0f0>";
    for (int i = 0; i < colCount; i++){
        if (!ui->tableView->isColumnHidden(i)){
            out<<QString("<th>%1</th>").arg(ui->tableView->model()->data(ui->tableView->model()->index(0, i)).toString().simplified());
        }
    }
    out<<"</tr></thead>\n";

    for (int j = 1; j < rowCount; j++) {
        out<<"<tr>";
        for (int i = 0; i < colCount; i++) {
            if (!ui->tableView->isColumnHidden(i)){
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(j, i)).toString().simplified();
                out<<QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out<<"</tr>\n";
    }
    out<<"</table></p>\n";
    out<<QString("<p><img src=%1 width=700 height=250></p>").arg(fileName);
    out<<"</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

//Arbol binario

void MainWindow::on_actionCreated_Binary_Tree_triggered()
{
    incrementox = 0;
    incrementoy = 0;
    inicio();
    float data;
    for(int j = 1; j < mModel->rowCount() - 1; j++){
        if(j == 1){
            data = getValueAt(mModel->rowCount() - 1, 2).toFloat();
            insertar(arbol, data);
        }
        data = getValueAt(j, 2).toFloat();
        insertar(arbol, data);
    }
    countNodo++;
    verArbol(arbol, 0);
    /*
    int width = ui->centralwidget->size().width();
    int height = ui->centralwidget->size().height();
    QPixmap pixmap(width / 2, height / 2);
    QPainter painter(&pixmap);
    QPen pen;
    painter.setBrush(Qt::black);
    //pen.setColor(Qt::black);
    int _w = tree->size().width();
    int _h = tree->size().height();
    painter.drawEllipse(QPoint(_w-150, 35),30,30);
    painter.drawEllipse(QPoint(_w/2, 100),30,30);
    painter.drawEllipse(QPoint(_w/4, 165),30,30);
    painter.drawEllipse(QPoint(_w/6, 230),30,30);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawText(width/4, 35, 23, 30, 0, "100");
    tree->setPixmap(pixmap);
    ui->gridLayout_3->addWidget(tree, 0, 1);*/
}

ABB MainWindow::crearNodo(int x)
{
    ABB nuevoNodo = new(struct nodo);
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

void MainWindow::insertar(ABB &arbol, int x)
{
    if(arbol==NULL){
        arbol = crearNodo(x);
    }else if(x < arbol->nro){
        insertar(arbol->izq, x);
    }else if(x > arbol->nro){
        insertar(arbol->der, x);
    }
}

void MainWindow::verArbol(ABB arbol, int n)
{
    if(countNodo == 1){
        x1 = ui->centralwidget->size().width() / 4;
        //y1 = ui->centralwidget->size().height() / 4;
    }
    if(arbol == NULL){
        return;
    }
    verArbol(arbol->izq, n + 1);
    incrementoy = 0;
    for(int i = 0; i < n; i++){
        incrementoy = incrementoy + 50;
    }
    esfera(radio,x1,y1,incrementox,incrementoy,QString::number(arbol->nro),Qt::yellow,Qt::black);
    incrementox = incrementox + 40;
    incrementoy = incrementoy + 40;
    verArbol(arbol->der, n + 1);
}

void MainWindow::enOrden(ABB arbol)
{
/*    if(arbol!=NULL){
        enOrden(arbol->izq);
        ui->ver->insertPlainText(QString::number(arbol->nro)+"-");
        qDebug() << arbol->nro << " ";
        enOrden(arbol->der);
    }*/
}

void MainWindow::inicio()
{
    pixmap = QPixmap(ui->centralwidget->size().width() / 2, ui->centralwidget->size().height() / 2);
    pixmap.fill(Qt::white);
}

void MainWindow::esfera(int radio, int x, int y, int incrementox, int incrementoy, QString texto, QColor colorfondo, QColor colorlinea)
{
    QPainter painter(&pixmap);
    if (incrementox == 0){
        painter.setBrush(colorfondo);
    }else{
        painter.setBrush(Qt::gray);
    }
    QPen pen(colorlinea);
    painter.setPen(pen);
    painter.drawEllipse(x+incrementox,y+incrementoy,radio,radio);
    painter.setPen(pen);
    painter.drawText(x+incrementox+12,y+incrementoy+20,texto);
    tree->setPixmap(pixmap);
    ui->gridLayout_3->addWidget(tree, 0, 1);
}
