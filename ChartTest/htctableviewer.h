#ifndef HTCTABLEVIEWER_H
#define HTCTABLEVIEWER_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QModelIndex>
#include <QDebug>


namespace Ui {
class HTCTableViewer;
}

class HTCTableViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit HTCTableViewer(QWidget *parent = 0);
    ~HTCTableViewer();



signals:


private slots:

    void on_tblFileData_sectionClicked(int Value);
    void on_btnClose_clicked();
//    void ChartDataSetsReceived(QVector <HTCChartDataSet> DataSets);

private:
    Ui::HTCTableViewer *ui;


    // functions
    void enableSelectedColumn(int columnNumber);

    void listSelectedColumns();
};

#endif // HTCTABLEVIEWER_H
