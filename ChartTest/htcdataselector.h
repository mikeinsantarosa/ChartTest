#ifndef HTCDATASELECTOR_H
#define HTCDATASELECTOR_H

#include <QMainWindow>
#include <QDebug>
#include <QFileInfoList>
#include <QDir>
#include <QTreeWidget>

#include "htcchartfolder.h"
#include "htcchartdatafile.h"

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



private:
    Ui::HTCDataSelector *ui;

    QString _folderInService;
    QString _filterInService;


    QStringList _folderList;

    HTCChartFolder * cdf;

    void FillListFromPath();


    void fillTree();
};

#endif // HTCDATASELECTOR_H
