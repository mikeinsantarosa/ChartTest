#ifndef HTCCHARTDATAMANGLER_H
#define HTCCHARTDATAMANGLER_H

#include <QObject>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

#include "htcchartdatafile.h"
#include "htcchartdataset.h"

#include "htcchart.h"

#include <algorithm>




class HTCChartDataMangler : public QObject
{
    Q_OBJECT
public:
    explicit HTCChartDataMangler(QObject *parent = nullptr);

    void Init(QStringList fileList, QVector <int> columns);
    bool GetItitializedDataOK();


signals:

    void ChartDataSetsReady(QVector <HTCChartDataSet> DataSets);

    void sendMsg(QString msg);

    //emit ChartDataSetsReady(_dataSets);

public slots:


private:

    // debug functions
    void listFiles();
    void listDataFiles();
    void listDataSets();
    void listThisList(QStringList list);

    void listTheFileStates();
    void listTheRangeFileStates();



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

    bool getMetrics();
    int getFileSetStatus();

    void showBadFileDataMessage(QString key);

    void setFilesPerRange();
    int getNumberOfFilesPerRange(QString range, int rangeID);

    void setRowCountsStatus();
    int setRowCountStatusByRange(QString range, int rangeID);

    void BuildAllChartDataSets();
    QStringList BuildDataSet(QString columns);

    QStringList getDataSetHeader(QString columns, int startFileNum, int stopFileNum, bool LoadFromFilePositions);
    QStringList getDataChunkByRange(QStringList list, QString columns, int range);

    void setDataSetProperties(HTCChartDataSet * ChartDataSet, QString columns, int chartNumber);

    bool _initialized = false;
    QStringList _columnSets;
    QStringList _baseFileList;
    QStringList _headerList;
    QStringList _rangeList;
    int _numberOfRanges;
    int _numberOfChartsToBuild;
    QString _dataFileDelim;

//    maybe add gets for these
//
//    _numberOfChartsToBuild
//    int _numberOfRanges
//    QStringList _rangeList
//    int NumFilesPerRange[3]
//    int RowCountsGoodPerRange[3]

    bool _loadHeaderFromFilePositions = true;

    double _lastFreqInList;

    int FileStartIDX[3] = {-1,-1,-1};
    int FileStopIDX[3] = {-1,-1,-1};
    int NumFilesPerRange[3] = {-1,-1,-1};
    int RowCountsGoodPerRange[3] = {-1,-1,-1};

    QMap <int,QStringList> RowCountsPerFile;

    QVector <int> _selectedColumns;
    QVector <int> _rangeIDList;
    QVector <HTCChartDataFile> _dataFiles;


    //QVector <QStringList> _dataSets;

    QVector  <HTCChartDataSet>  _dataSets;
    HtcChart * testchart;




};

#endif // HTCCHARTDATAMANGLER_H
