#ifndef HTCCHARTDATAMANGLER_H
#define HTCCHARTDATAMANGLER_H

#include <QObject>
#include <QDebug>

#include "htcchartdatafile.h"
#include <algorithm>


class HTCChartDataMangler : public QObject
{
    Q_OBJECT
public:
    explicit HTCChartDataMangler(QObject *parent = nullptr);

    void Init(QStringList fileList, QVector <int> columns);
    //


signals:

public slots:


private:
    int findFirstDataRow(QStringList list, QString delimiter);
    int setLastDataRow();
    void setDataFileDelim(QString fileName);
    void loadFilesIntoData();

    void listFiles();
    void listDataFiles();

    bool _initialized = false;

    QStringList _baseFileList;
    QStringList _headerList;
    QVector <int> _selectedColumns;
    QVector <int> _rangeIDList;
    QVector <HTCChartDataFile>  _dataFiles;

    //bool operator<(const HTCChartDataFile& a, const HTCChartDataFile& b) { return a._sortOrderIDX < b._sortOrderIDX; }


};

#endif // HTCCHARTDATAMANGLER_H
