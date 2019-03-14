#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPen>
#include <QCategoryAxis>
#include <QPalette>

#include "loggraph.h"
#include "lineargraph.h"
#include "htcchart.h"
#include "htcchartdatafile.h"
#include "datamanager.h"
#include "htctableviewer.h"
#include "htcdatadialog.h"

#include <QDirIterator>

// for the tutorials
#include "htcmodel.h"
#include <QTableView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnLogGraph_clicked();

    void on_btnCustomGraph_clicked();

    void on_btnClose_clicked();

    void on_btnShowTestChart_clicked();

    void on_btnSetColor_clicked();

    void on_btnOpenFolders_clicked();

    void on_btnChangeDate_clicked();

    void on_btnShowTable_clicked();

    void on_btnLoadFile_clicked();

    void on_btnTutorial_clicked();

    void on_btnTest_clicked();

private:
    Ui::MainWindow *ui;

    LogGraph * logGraph;
    LinearGraph * linGraph;
    HtcChart * testchart;
    DataManager * dm;
    HtcDataDialog * dd;

    QStringList getListToLoad();

    QString getDelimToUse(QString fName);

    void listFiles(QStringList * flist, QDir directory, QString indent, QString fExtension);

    int loadListFromPath(QString dir, QString fileExtension);

    QStringList getFileList();
};

#endif // MAINWINDOW_H
