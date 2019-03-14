#ifndef HTCDATASETITEM_H
#define HTCDATASETITEM_H

#include <QDebug>
#include <QVector>
#include "htcchartdatafile.h"


class HTCDataSetItem
{
public:
    HTCDataSetItem();
    HTCDataSetItem(QString model, QString serial);

    QString GetModel() const;
    QString GetSerial() const;
    // not sure this is needed
    QString GetKey();

    void SetModel(QString model);
    void SetSerial(QString serial);

    void AddFileToSet(HTCChartDataFile file);

    QVector <HTCChartDataFile> * GetFileSet();



private:

    QVector <HTCChartDataFile> * _fileset;
    int _numberOfFiles;
    QString _model;
    QString _serial;

    // not sure this is needed
    QString _key;

    void updateKey();

};

#endif // HTCDATASETITEM_H
