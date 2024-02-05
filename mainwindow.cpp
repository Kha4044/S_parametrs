#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include <QApplication>
#include <QAxObject>
#include <QDebug>
#include <QAxBase>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0, 1000, this));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 1000, this));


}


void MainWindow::setupVNA()
{

    pNWA->querySubObject("SCPI")->querySubObject("SYSTem")->dynamicCall("PRESet()");//перезагрузка
    pNWA->querySubObject("SCPI")->querySubObject("DISPlay")->querySubObject("WINDow(1)")->dynamicCall("ACTivate()");//назначение акивного канала


    pNWA->querySubObject("SCPI")->querySubObject("INITiate(1)")->setProperty("CONTinuous",1);//нужен для тригера


    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter")->setProperty("COUNt",4);

    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", "PHASe"); //формат








}

void MainWindow::setupS11()
{

    pNWA->querySubObject("SCPI")->querySubObject("SENSe(1)")->querySubObject("FREQuency")->setProperty("STARt", min);

    pNWA->querySubObject("SCPI")->querySubObject("SENSe(1)")->querySubObject("FREQuency")->setProperty("STOP", max);

    pNWA->querySubObject("SCPI")->querySubObject("SENSe(1)")->querySubObject("SWEep")->setProperty("POINts",count);


    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->setProperty("DEFine","S11");


    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->setProperty("DEFine","S12");

    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->setProperty("DEFine","S21");

    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->setProperty("DEFine","S22");

    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", "UPHase");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", "UPHase");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", "UPHase");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
    pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", "UPHase");

    pNWA->querySubObject("SCPI")->querySubObject("TRIGger")->querySubObject("SEQuence")->setProperty("SOURce","BUS");
    pNWA->querySubObject("SCPI")->querySubObject("TRIGger")->querySubObject("SEQuence")->setProperty("WAIT","HOLD");
    pNWA->querySubObject("SCPI")->querySubObject("TRIGger")->querySubObject("SEQuence")->dynamicCall("SINGle()");
    QAxObject *pDataS11 = pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(1)")->querySubObject("DATA");
    QAxObject *pDataS12 = pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(2)")->querySubObject("DATA");
    QAxObject *pDataS21 = pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(3)")->querySubObject("DATA");
    QAxObject *pDataS22 = pNWA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(4)")->querySubObject("DATA");
    QVariant DataS11 = pDataS11->dynamicCall("FDATa");
    QVariant DataS12 = pDataS12->dynamicCall("FDATa");
    QVariant DataS21 = pDataS21->dynamicCall("FDATa");
    QVariant DataS22 = pDataS22->dynamicCall("FDATa");



    if (DataS11.canConvert<QVariantList>())

    {

        QVariantList dataListS11 = DataS11.toList();
        QVariantList dataListS12 = DataS12.toList();
        QVariantList dataListS21 = DataS21.toList();
        QVariantList dataListS22 = DataS22.toList();

        for ( int n = 0; n < dataListS11.length()/2; ++n)


        {

            yS11.push_back(dataListS11[n*2].toDouble());
            yS12.push_back(dataListS12[n*2].toDouble());
            yS21.push_back(dataListS21[n*2].toDouble());
            yS22.push_back(dataListS22[n*2].toDouble());


            x.push_back(n);


        }
        qDebug() << "s11" << "\t";
        qDebug() << yS11 << "\t";
        qDebug() << "s12" << "\t";
        qDebug() << yS12 << "\t";
        qDebug() << "s21" << "\t";
        qDebug() << yS21 << "\t";
        qDebug() << "s22" << "\t";
        qDebug() << yS22 << "\t";


    }

    else


    {

        qDebug() << "Device not ready";

    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
    int index1, index2;
    min=ui->lineEdit->text().toFloat();
    max=ui->lineEdit_2->text().toFloat();
    index1=ui->comboBox_5->currentIndex();
    index2=ui->comboBox_6->currentIndex();
    count=ui->lineEdit_3->text().toInt();


    switch(index1)
    {
    case 0:
        min=min*1000;
        break;

    case 1:
        min=min*1000000;
        break;

    case 2:
        min=min*1000000000;
        break;


    }

    switch(index2)
    {
    case 0:
        max=max*1000;
        break;
    case 1:
        max=max*1000000;
        break;
    case 2:
        max=max*1000000000;
        break;
    }
    setupVNA();
    setupS11();
    setupPlot();



\
    ui->horizontalScrollBar->setRange(-min, max);
    ui->verticalScrollBar->setRange(-500, 500);
    qDebug()<<min;
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    ui->plot->xAxis->setRange(min, max);
    ui->plot->yAxis->setRange(-50, 50);
}


void MainWindow::setupPlot()
{
    ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    ui->plot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(9);
    ui->plot->legend->setFont(legendFont);
    ui->plot->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);



    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::blue));
    ui->plot->graph()->setName(QString("S11"));
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::green));
    ui->plot->graph()->setName(QString("S12"));
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::red));
    ui->plot->graph()->setName(QString("S21"));
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::black));
    ui->plot->graph()->setName(QString("S22"));
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::yellow));
    ui->plot->graph()->setName(QString("ДП"));


    h=(max-min)/count;
    for (int i=0; i<count; i++)
    {

        x[i]=min+x[i]*h;

    }
    if(ui->checkBox->isChecked())
        ui->plot->graph(0)->addData(x, y1);
    else
        ui->plot->graph(0)->addData(0, 0);
    if(ui->checkBox_2->isChecked())
        ui->plot->graph(1)->addData(x, yS12);
    else
        ui->plot->graph(1)->addData(0,0);
    if(ui->checkBox_3->isChecked())
        ui->plot->graph(2)->addData(x,yS21);
    else
        ui->plot->graph(2)->addData(0,0);
    if(ui->checkBox_4->isChecked())
        ui->plot->graph(3)->addData(x,yS22);
    else
        ui->plot->graph(3)->addData(0,0);
    if(ui->checkBox_5->isChecked())
        ui->plot->graph(4)->addData(x,Real);
    else
        ui->plot->graph(4)->addData(0,0);


    ui->plot->graph(0)->rescaleAxes();
    ui->plot->graph(1)->rescaleAxes();
    ui->plot->graph(2)->rescaleAxes();
    ui->plot->graph(3)->rescaleAxes();


    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::horzScrollBarChanged(int value)
{
    if (qAbs(ui->plot->xAxis->range().center()-value/100.0) > 0.01)
    {
        ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(), Qt::AlignCenter);
        ui->plot->replot();
    }
}

void MainWindow::vertScrollBarChanged(int value)
{
    if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01)
    {
        ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
        ui->plot->replot();
    }
}

void MainWindow::xAxisChanged(QCPRange range)
{
    ui->horizontalScrollBar->setValue(qRound(range.center()*100.0));
    ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0));
}

void MainWindow::yAxisChanged(QCPRange range)
{
    ui->verticalScrollBar->setValue(qRound(-range.center()*100.0));
    ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0));


}



MainWindow::~MainWindow()
{
    delete ui;
}


