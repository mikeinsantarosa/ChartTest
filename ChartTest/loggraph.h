#ifndef LOGGRAPH_H
#define LOGGRAPH_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPen>
#include <QCategoryAxis>
#include <QChart>
#include <QLineSeries>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class LogGraph;
}

class LogGraph : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogGraph(QWidget *parent = 0);
    ~LogGraph();

private slots:
    void on_btnClose_clicked();

    void on_btnSetValue_clicked();

    void on_btnRemoveChart_clicked();

    void on_btnReplaceChart_clicked();

private:
    Ui::LogGraph *ui;

    // chart peices
    QCategoryAxis *axisX;
    QCategoryAxis *axisY;
    QLinearGradient backgroundGradient;
    QLinearGradient plotAreaGradient;
    QChartView *chartView;

    void removechart();
    void replaceChart();

    void clearLayout(QLayout *layout);



};

#endif // LOGGRAPH_H
