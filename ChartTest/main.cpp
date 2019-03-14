#include "mainwindow.h"
#include <QApplication>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPen>
#include <QCategoryAxis>

// tutorials
#include "htcmodel.h"
#include <QTableView>


QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    // tutorials
    QTableView tableView;

    /* Interesting!
     *
     * If your class uses QObject
     * pass a 0 as the argument
     * in the constructor
     * for it.
     *
     * No other value seems to work
     *
     * This has been a stumbling block
     * for a while!
    */


//    HTCModel myModel(0);
//    tableView.setModel( &myModel );
//    qDebug() << "Calling show()...";
//    tableView.show();

    return a.exec();
}
