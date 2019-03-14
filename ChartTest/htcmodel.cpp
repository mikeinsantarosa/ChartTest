#include "htcmodel.h"

HTCModel::HTCModel(QObject * parent)
        :QAbstractTableModel(parent)
{
    //qDebug() << "HTCModel constructor called...";
}

int HTCModel::rowCount(const QModelIndex &parent) const
{
    //qDebug() << "rowCount called...";
    return 2;
}

int HTCModel::columnCount(const QModelIndex &parent) const
{
    //qDebug() << "columnCount called...";
    return 3;
}

QVariant HTCModel::data(const QModelIndex &index, int role) const
{

    int row = index.row();
        int col = index.column();

        switch(role){
        case Qt::DisplayRole:
            qDebug() << "role received = Qt::DisplayRole #" << role;
            if (row == 0 && col == 1) return QString("<--left");
            if (row == 1 && col == 1) return QString("right-->");

            return QString("Row%1, Column%2")
                    .arg(row + 1)
                    .arg(col +1);
            break;
        case Qt::FontRole:
            if (row == 0 && col == 0) //change font only for cell(0,0)
            {

                qDebug() << "role received = Qt::FontRole #" << role;
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }
            break;
        case Qt::BackgroundRole:

            if (row == 1 && col == 2)  //change background only for cell(1,2)
            {
                qDebug() << "role received = Qt::BackgroundRole #" << role;
                QBrush redBackground(Qt::red);
                return redBackground;
            }
            break;
        case Qt::TextAlignmentRole:

            if (row == 1 && col == 1) //change text alignment only for cell(1,1)
            {
                qDebug() << "role received = Qt::TextAlignmentRole #" << role;
                return Qt::AlignRight + Qt::AlignVCenter;
            }
            break;
        case Qt::CheckStateRole:

            if (row == 1 && col == 0) //add a checkbox to cell(1,0)
            {
                qDebug() << "role received = Qt::CheckStateRole: #" << role;
                return Qt::Checked;
            }
        }
        return QVariant();
}
