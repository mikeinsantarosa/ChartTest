
#include "htctableviewer.h"
#include "ui_htctableviewer.h"

HTCTableViewer::HTCTableViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HTCTableViewer)
{
    ui->setupUi(this);

    QObject::connect( ui->tblFileData->horizontalHeader(), SIGNAL( sectionClicked( int ) ), this, SLOT( on_tblFileData_sectionClicked( int ) ) );

    QStandardItemModel *model = new QStandardItemModel(6,3,this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column 1 Header")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column 2 Header")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column 3 Header")));

    ui->tblFileData->setModel(model);

    const auto selectedIndexes = ui->tblFileData->selectionModel()->selectedIndexes();
    for(auto&& singleIndex : selectedIndexes)
    {
        qDebug() << "row: " << singleIndex.row() << " col: " << singleIndex.column()  << " data: " << singleIndex.data();
    }
    
    ui->tblFileData->selectColumn(0);

}

HTCTableViewer::~HTCTableViewer()
{
    delete ui;
}

void HTCTableViewer::on_tblFileData_sectionClicked(int Value)
{
    qDebug() << "Clicked a Column" << Value;
    listSelectedColumns();
    if (Value==0)
    {
        //isColumnSelected
    }
}

void HTCTableViewer::on_btnClose_clicked()
{
    this->close();
}

void HTCTableViewer::enableSelectedColumn(int columnNumber)
{
    //ui->tblFileData->selectColumn(columnNumber);
}


void HTCTableViewer::listSelectedColumns()
{
    qDebug() << "In listSelectedColumns()...";
    QString del = ";";
    QString values = "";
    QString value;
    int col;

    const auto selectedIndexes = ui->tblFileData->selectionModel()->selectedIndexes();
    for(auto&& singleIndex : selectedIndexes)
    {
        //qDebug() << "row: " << singleIndex.row() << " col: " << singleIndex.column()  << " data: " << singleIndex.data();
        col = singleIndex.column();
        value = QString::number(col);
        qDebug() << "col = " << col << " value = " << value;

        if (!values.contains(value))
        {
            values.append(value);
            values.append(del);
        }
        qDebug() << " values " << values;
    }
}
