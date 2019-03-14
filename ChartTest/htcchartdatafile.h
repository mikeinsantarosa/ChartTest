#ifndef HTCCHARTDATAFILE_H
#define HTCCHARTDATAFILE_H

//#include <QObject>
#include <QFileInfo>
#include <QDebug>
#include "datapoint.h"


class HTCChartDataFile
{

public:
    explicit HTCChartDataFile(QString dataFileName = "", QString fileDelimiter = "," );

    QVector <DataPoint> getAllPoints();

    QStringList getColumnHeaderList();
    bool getDataSuccessfullyLoaded();
    int getFirstDataRowNumber();
    int getlastDataRowNumber();
    double getFirstFreq();
    double getLastFreq();
    int getColumnHeadersRowNumber();
    int getTotalNumberOfRows();
    QFileInfo getDataFileInfo();
    QString getOrientationPolarity();
    QString getOrientationTTRotation();
    QString getOrientationFRange();
    QString getOrientationTLevel();
    QString getOrientationEUTSerial();
    QString getOrientationEUTModel();
    QString getOrientationTestCode();
    int getOrientationRangeIndex();
    int getOrientationOrderIndex();





signals:

public slots:

private:



    QFileInfo _fileInfo;
    QString _basedOnThisFile;
    QString _fileDelimiter;
    bool _dataSuccessfullyLoaded;
    int _totalNumberOfRows;
    int _firstDataRow;
    int _lastDataRow;
    int _headerDataRow;
    int _numberOfDataColumns;
    QStringList _rawDataList;
    QStringList _ColumnHeaderlist;

    // file sort properties
    QString _polarity;
    QString _ttRotation;
    QString _fRange;
    QString _tLevel;
    QString _eutSerial;
    QString _eutModel;
    QString _testCode;

    int _rangeIDX;
    int _orientationOrderIDX;
    int _sortOrderIDX;

    // data values
    double _firstFreq;
    double _lastFreq;

    void init();

    int findFirstDataRow(QString delimiter);
    int setLastDataRow();
    int loadFileIntoList();
    int setColumnHeadersList(QString delim);
    void parseFileProperties();

    int solveRangeIDX(QString rangeString);
    int solveOrientationIDX(QString polarity, QString rotation);
    int setSortOrderIndex();

    // file data
    QVector <DataPoint> _allPoints;
    void loadDataIntoMemory();

    void setFilenameProperties(QString fName);
    void setFirstFreq();
    void setLastFreq();


};

#endif // HTCCHARTDATAFILE_H
