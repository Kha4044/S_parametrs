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

    ui->BasicLineEdit->setValidator(new QIntValidator(0, 1000, this));
    ui->FinalLineEdit->setValidator(new QIntValidator(0, 1000, this));
    ui->PointsLineEdit->setValidator(new QIntValidator(2, 2002, this));
    setupVNA();
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));



}


void MainWindow::setupVNA()
{

    S2VNA->querySubObject("SCPI")->querySubObject("SYSTem")->dynamicCall("PRESet()");//перезагрузка
    S2VNA->querySubObject("SCPI")->querySubObject("DISPlay")->querySubObject("WINDow(1)")->dynamicCall("ACTivate()");//назначение акивного канала
    S2VNA->querySubObject("SCPI")->querySubObject("INITiate(1)")->setProperty("CONTinuous",1);//нужен для тригера
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter")->setProperty("COUNt",4);//установка количества измеряемых графиков
    // Эквивалентная COM команда

    //     SCPI.IEEE4882.OPC

    //             Синтаксис

    //     Value = app.SCPI.IEEE4882.OPC

    //               app.SCPI.IEEE4882.OPC = Dummy
// app.SCPI.TRIGger.SEQuence.SINGle

}

void MainWindow::setupSparametr()
{    S2VNA->querySubObject("SCPI")->querySubObject("TRIGger")->querySubObject("SEQuence")->setProperty("SOURce","BUS");//Установка срабатывания тригера от приложения

    int TypeMesuare=ui->TypeComboBox->currentIndex();
    S2VNA->querySubObject("SCPI")->querySubObject("TRIGger")->querySubObject("SEQuence")->dynamicCall("SINGle()");
    S2VNA->querySubObject("SCPI")->querySubObject("IEEE4882")->dynamicCall("OPC");

    S2VNA->querySubObject("SCPI")->querySubObject("SENSe(1)")->querySubObject("FREQuency")->setProperty("STARt", _min);

    S2VNA->querySubObject("SCPI")->querySubObject("SENSe(1)")->querySubObject("FREQuency")->setProperty("STOP", _max);

    S2VNA->querySubObject("SCPI")->querySubObject("SENSe(1)")->querySubObject("SWEep")->setProperty("POINts",_Point);


    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->setProperty("DEFine","S11");


    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->setProperty("DEFine","S12");

    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->setProperty("DEFine","S21");

    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->setProperty("DEFine","S22");
    // Амп лог MLOGarithmic
    //     КСВН SWR
    //         Фаза PHASe
    //             Фаза 180
    //                 ГВЗ GDELog
    //                     АМП лин
    //                         Реал REAL
    //                             МНим IMAGinary
    // const char *_AmpLog="MLOGarithmic", *_KSVN="SWR", *_PHASe="PHASe",*Fase180="UPHase", *_GVZ="GDEL", *_AmpLin="MLINear", *_REAL="REAL", *_MNIM="IMAGinary";
    switch  (TypeMesuare){
    case 0:
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLog);
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLog);
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLog);
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
    S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLog);
    break;
    case 1:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _KSVN);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _KSVN);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _KSVN);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _KSVN);
        break;
    case 2:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _PHASe);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _PHASe);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _PHASe);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _PHASe);
        break;
    case 3:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _Fase180);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _Fase180);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _Fase180);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _Fase180);
        break;
    case 4:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _GVZ);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _GVZ);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _GVZ);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _GVZ);
        break;

    case 5:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLin);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLin);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLin);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _AmpLin);
        break;

    case 6:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _REAL);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _REAL);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _REAL);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _REAL);
        break;

    case 7:
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(1)")->dynamicCall("SElect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _MNIM);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(2)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _MNIM);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(3)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _MNIM);
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("PARameter(4)")->dynamicCall("SELect()");
        S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("SELected")->setProperty("FORMat", _MNIM);
        break;
    }

    QAxObject *pDataS11 = S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(1)")->querySubObject("DATA");
    QAxObject *pDataS12 = S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(2)")->querySubObject("DATA");
    QAxObject *pDataS21 = S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(3)")->querySubObject("DATA");
    QAxObject *pDataS22 = S2VNA->querySubObject("SCPI")->querySubObject("CALCulate(1)")->querySubObject("TRACe(4)")->querySubObject("DATA");
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

        for ( int i = 0; i < dataListS11.length()/2; i++)


        {

            _yS11.push_back(dataListS11[i*2].toDouble());
            _yS12.push_back(dataListS12[i*2].toDouble());
            _yS21.push_back(dataListS21[i*2].toDouble());
            _yS22.push_back(dataListS22[i*2].toDouble());


            _x.push_back(i);


        }
        qDebug() << "s11" << "\t";
        qDebug() << _yS11 << "\t";
        qDebug() << "s12" << "\t";
        qDebug() << _yS12 << "\t";
        qDebug() << "s21" << "\t";
        qDebug() << _yS21 << "\t";
        qDebug() << "s22" << "\t";
        qDebug() << _yS22 << "\t";


    }

    else


    {

        qDebug() << "Device not ready";

    }
}


void MainWindow::on_Measure_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
    int MultiplierMin, MultiplierMax;
    _min=ui->BasicLineEdit->text().toFloat();
    _max=ui->FinalLineEdit->text().toFloat();
    MultiplierMin=ui->MultiplierBasicComboBox->currentIndex();
    MultiplierMax=ui->MultiplierFinalComboBox->currentIndex();
    _Point=ui->PointsLineEdit->text().toInt();

    if (ui->BasicLineEdit->displayText().isEmpty())
        _min=100000;
    else
    {
    switch(MultiplierMin)
    {
    case 0:
        _min=_min*_k;
        break;

    case 1:
        _min=_min*_M;
        break;

    case 2:
        _min=_min*_G;
        break;


    }}

if (ui->FinalLineEdit->displayText().isEmpty())
        _max=1000000000;
else
{
    switch(MultiplierMax)
    {
    case 0:
        _max=_max*_k;
        break;
    case 1:
        _max=_max*_M;
        break;
    case 2:
        _max=_max*_G;
        break;
    }
}
    setupSparametr();
    setupPlot();


    ui->plot->xAxis->setRange(_min, _max);
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
    ui->plot->graph()->setPen(QPen(Qt::cyan));
    ui->plot->graph()->setName(QString("ДП"));


    _h=(_max-_min)/_Point;
    for (int i=0; i<_Point; i++)
    {

        _x[i]=_min+_x[i]*_h;

    }
    if(ui->S11CheckBox->isChecked())
        ui->plot->graph(0)->addData(_x, _yS11);
    else
        ui->plot->graph(0)->addData(0, 0);
    if(ui->S21CheckBox->isChecked())
        ui->plot->graph(1)->addData(_x, _yS12);
    else
        ui->plot->graph(1)->addData(0,0);
    if(ui->S12checkBox->isChecked())
        ui->plot->graph(2)->addData(_x,_yS21);
    else
        ui->plot->graph(2)->addData(0,0);
    if(ui->S22checkBox->isChecked())
        ui->plot->graph(3)->addData(_x,_yS22);
    else
        ui->plot->graph(3)->addData(0,0);
    if(ui->DPCheckBox->isChecked())
        ui->plot->graph(4)->addData(_x,_DP);
    else
        ui->plot->graph(4)->addData(0,0);


    ui->plot->graph(0)->rescaleAxes();
    ui->plot->graph(1)->rescaleAxes();
    ui->plot->graph(2)->rescaleAxes();
    ui->plot->graph(3)->rescaleAxes();


    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}





MainWindow::~MainWindow()
{
    delete ui;
}

