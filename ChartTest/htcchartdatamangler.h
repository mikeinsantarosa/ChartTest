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
    bool GetItitializedDataOK();


signals:

public slots:


private:

    // debug functions
    void listFiles();
    void listDataFiles();
    void listDataSets();
    void listThisList(QStringList list);



    int findFirstDataRow(QStringList list, QString delimiter);
    void setDataFileDelim(QString fileName);
    void loadFilesIntoData();
    bool sortFileset();

    void discoverRanges();
    void discoverStartStopRangeIDs();
    int discoverStartRangeID(QString range);
    int discoverStopRangeID(QString range);
    void setNumberOfChartsTobuild();
    void setColumnLists();
    void setFileDelim();

    void BuildAllChartDataSets();
    QStringList BuildDataSet(QString columns);

    QStringList getDataSetHeader(QString columns, int startFileNum, int stopFileNum);
    QStringList getDataChunkByRange(QStringList list, QString columns, int range);


    bool _initialized = false;
    QStringList _columnSets;
    QStringList _baseFileList;
    QStringList _headerList;
    QStringList _rangeList;
    int _numberOfRanges;
    int _numberOfChartsToBuild;
    QString _dataFileDelim;

    int FileStartIDX[3] = {-1,-1,-1};
    int FileStopIDX[3] = {-1,-1,-1};

    QVector <int> _selectedColumns;
    QVector <int> _rangeIDList;
    QVector <HTCChartDataFile> _dataFiles;


    QVector <QStringList> _dataSets;




};

#endif // HTCCHARTDATAMANGLER_H