#ifndef PLOTS_H
#define PLOTS_H
#include "qcustomplot.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Plots
{
public:
    Plots();
    void setupPlot();

private slots:
    void horzScrollBarChanged(int value);
    void vertScrollBarChanged(int value);
    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);

};

#endif // PLOTS_H
