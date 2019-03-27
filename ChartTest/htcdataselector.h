#ifndef HTCDATASELECTOR_H
#define HTCDATASELECTOR_H

#include <QMainWindow>
#include <QDebug>
#include <QFileInfoList>
#include <QDir>
#include <QTreeWidget>

#include "htcchartfolder.h"
#include "htcchartdatafile.h"
#include "htcdatadialog.h"
#include "htcchartdatamangler.h"


namespace Ui {
class HTCDataSelector;
}

class HTCDataSelector : public QMainWindow
{
    Q_OBJECT

public:
    explicit HTCDataSelector(QWidget *parent = nullptr);
    ~HTCDataSelector();


void SetFolderInService(QString folder, QString filter);



private slots:
    void on_btnClose_clicked();
    void mySlot_Changed();
    void ColumnsHaveBeenSelected();
    void receivedMsg(QString msg);
    void ChartDataSetsReceived(QVector <HTCChartDataSet> DataSets);



    void on_btnSelectColumns_clicked();


private:
    Ui::HTCDataSelector *ui;


    QString _folderInService;
    QString _filterInService;


    QStringList _folderList;

    QStringList _taggedList;
    QVector <int> _selectedColumnsList;

    HTCChartFolder * cdf;
    HtcDataDialog * dd;
    HTCChartDataMangler * dm;

    void FillListFromPath();
    void fillTree();

    void FillTaggedList(QTreeWidgetItem * item);
};

#endif // HTCDATASELECTOR_H
