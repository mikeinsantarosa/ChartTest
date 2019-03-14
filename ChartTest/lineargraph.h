#ifndef LINEARGRAPH_H
#define LINEARGRAPH_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPen>
#include <QCategoryAxis>
#include <QChart>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class LinearGraph;
}

class LinearGraph : public QMainWindow
{
    Q_OBJECT

public:
    explicit LinearGraph(QWidget *parent = 0);
    ~LinearGraph();

private slots:
    void on_btnClose_clicked();

private:
    Ui::LinearGraph *ui;
};

#endif // LINEARGRAPH_H
