#ifndef HTCFILELIBRARY_H
#define HTCFILELIBRARY_H

#include <QDebug>
#include <QStringList>
#include "htcchartdatafile.h"
#include "htcdatasetitem.h"


class HTCFileLibrary
{
public:
    HTCFileLibrary(QVector <HTCChartDataFile> * library);

    int GetNumberOfDataSets();
    QVector <HTCDataSetItem> * GetDataSets();

private:

    QVector <HTCChartDataFile> * _masterLibrary;
    QVector <HTCDataSetItem> * _dataSets;

    /*
     *
     * discover how many data-sets (model + serial number) there.
     */

    // properties
    int _numberOfDataSets;
    int _numberOfFliesLoaded;


    // methods

    int getDataSetCount();
    void listDataSet();



};

#endif // HTCFILELIBRARY_H
