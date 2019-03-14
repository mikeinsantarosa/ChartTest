#ifndef HTCMODEL_H
#define HTCMODEL_H

#include <QObject>
#include <QDebug>
#include <QAbstractTableModel>
#include <QFont>
#include <QBrush>
#include <QModelIndex>

class HTCModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    HTCModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // HTCMODEL_H
