#include "htcdataselector.h"
#include "ui_htcdataselector.h"

HTCDataSelector::HTCDataSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HTCDataSelector)
{
    ui->setupUi(this);
    ui->btnPlot->setEnabled(false);
    ui->btnSelectColumns->setEnabled(false);

    // create new Chart Data Folder
    cdf = new HTCChartFolder;

    connect(ui->treeDatasets, SIGNAL(itemSelectionChanged()), this, SLOT(mySlot_Changed()));



}

HTCDataSelector::~HTCDataSelector()
{
    delete ui;
}

void HTCDataSelector::SetFolderInService(QString folder, QString filter)
{
    if(!folder.isEmpty())
    {
        _folderInService = folder;
        _filterInService = filter;
        cdf->init(_folderInService, _filterInService);

        FillListFromPath();

    }

}

void HTCDataSelector::on_btnClose_clicked()
{

    delete dd;
    close();
}

void HTCDataSelector::mySlot_Changed()
{
    int numberOfkids = -1;
    QString selectedSet = "";
    QTreeWidgetItem * item = ui->treeDatasets->currentItem();

    if (!item->parent())
    {
        numberOfkids = item->childCount();
        selectedSet.append("Selected Data set : ");
        selectedSet.append(item->text(0));
        selectedSet.append(" - Number of files = ");
        selectedSet.append(QString::number(numberOfkids));
        ui->labelSelectedDataSet->setText(selectedSet);

        FillTaggedList(item);

        ui->btnSelectColumns->setEnabled(true);

    }
}

void HTCDataSelector::ColumnsHaveBeenSelected()
{
    _selectedColumnsList = dd->getSelectedColumnsList();

    if(!_selectedColumnsList.isEmpty())
    {
        ui->btnPlot->setEnabled(true);
    }

//    for(int i = 0; i < _selectedColumnsList.count(); i++)
//    {
//        qDebug() << "selected column " << i << " is " << _selectedColumnsList.at(i);
//    }

}

void HTCDataSelector::FillListFromPath()
{
    QStringList s;

    if (!_folderList.isEmpty())
    {
        _folderList.clear();
    }
     _folderList = cdf->GetTaggedList();
     _folderList.sort();
    if(_folderList.count() > 0)
    {
        fillTree();
    }

}

void HTCDataSelector::fillTree()
{


            ui->treeDatasets->setHeaderLabel("Radiated Immunity Data - Find  your data and Click Select");


            QTreeWidgetItem *topLevelItem = NULL;
            foreach (const QString &fileName, _folderList)
            {
                QStringList splitFileName = fileName.split(",");

                // add keyed string as top level item if treeWidget doesn't already have it
                if (ui->treeDatasets->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
                {
                    topLevelItem = new QTreeWidgetItem;
                    topLevelItem->setText(0, splitFileName[0]);
                    ui->treeDatasets->addTopLevelItem(topLevelItem);

                }

                QTreeWidgetItem *parentItem = topLevelItem;

                // iterate through non-root directories (file name comes after)
                for (int i = 1; i < splitFileName.size() - 1; ++i)
                {
                    // iterate through children of parentItem to see if this directory exists
                    bool thisDirectoryExists = false;
                    for (int j = 0; j < parentItem->childCount(); ++j)
                    {
                        if (splitFileName[i] == parentItem->child(j)->text(0))
                        {
                            thisDirectoryExists = true;
                            parentItem = parentItem->child(j);
                            break;
                        }
                    }

                    if (!thisDirectoryExists)
                    {
                        parentItem = new QTreeWidgetItem(parentItem);
                        parentItem->setText(0, splitFileName[i]);
                    }
                }

                QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
                childItem->setText(0, splitFileName.last());
            }


}

void HTCDataSelector::FillTaggedList(QTreeWidgetItem *item)
{

    if (!_taggedList.isEmpty())
    {
        _taggedList.clear();
    }

    for (int i = 0; i < item->childCount(); i++)
    {
        _taggedList.append(item->child(i)->text(0));
    }

}

void HTCDataSelector::on_btnSelectColumns_clicked()
{
    QString file = _taggedList.at(0);

    if(_taggedList.count() > 0)
    {
        dd = new HtcDataDialog(this);
        dd->move(6,6);
        dd->Init(_taggedList.at(0));
        dd->show();

        connect(dd,SIGNAL(ColumnSelected()),this,SLOT(ColumnsHaveBeenSelected()));
    }

}

void HTCDataSelector::on_btnPlot_clicked()
{

    dm = new HTCChartDataMangler(this);
    dm->Init(_taggedList, _selectedColumnsList);

}
