#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QOpenGLWidget>
#include "qcustomplot.h"
#include <ActiveQt>
#include <QOpenGLWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupPlot();
    void setupSparametr();
    void setupVNA();




private slots:

    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);


    void on_Measure_clicked();
    // Амп лог MLOGarithmic
    //     КСВН SWR
    //         Фаза PHASe
    //             Фаза 180 UPHase
    //                 ГВЗ GDELog
    //                     АМП лин
    //                         Реал REAL
    //                             МНим IMAGinary
private:
    Ui::MainWindow *ui;
    QAxObject *S2VNA = new QAxObject("S2VNA.Application");
    int _Point;
    int _G=1000000000, _M=1000000, _k=1000;
    QVector <double> _x,_y, _yS11,_yS12,_yS21,_yS22, _DP;
    double _h, _min, _max, _minY, _maxY;
    const char *_AmpLog="MLOGarithmic", *_KSVN="SWR", *_PHASe="PHASe",*_Fase180="UPHase", *_GVZ="GDEL", *_AmpLin="MLINear", *_REAL="REAL", *_MNIM="IMAGinary";
};
#endif // MAINWINDOW_H
