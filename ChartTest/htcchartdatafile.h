#ifndef HTCCHARTDATAFILE_H
#define HTCCHARTDATAFILE_H

//#include <QObject>
#include <QFileInfo>
#include <QDebug>
#include <QRegExp>


#include "datapoint.h"


class HTCChartDataFile
{

public:
    explicit HTCChartDataFile(QString dataFileName );
    HTCChartDataFile();

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
    QString getKey();





signals:

public slots:

private:



    QFileInfo _fileInfo;
    QString _basedOnThisFile;
    QString _dataFileDelim;

    bool _dataSuccessfullyLoaded;
    int _totalNumberOfRows;
    int _firstDataRow;
    int _lastDataRow;
    int _headerDataRow;
    int _numberOfDataColumns;
    QStringList _rawDataList;
    QStringList _ColumnHeaderlist;
    int _isStandardTestType;
    QString _fileNamePartsDelim = "_";
    QStringList _standardTestRanges;//{"80M-1G","1G-2G","2G-27G","1G-6G"};
    QString _SetKey = "";

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

    int findFirstDataRow(QStringList list, QString delimiter);
    int setLastDataRow();
    int loadFileIntoList();
    int setColumnHeadersList(QString delim);
    void parseFileProperties();
    void setDataFileDelim(QString fileName);

    int solveRangeIDX(QString rangeString);
    int solveOrientationIDX(QString polarity, QString rotation);
    int setSortOrderIndex();

    void initProperties();

    // file data
    QVector <DataPoint> _allPoints;
    void loadDataIntoMemory();

    void setFilenameProperties(QString fName);
    void setFirstFreq();
    void setLastFreq();
    void setStandardTestType(QString rangeString);
    void setKey();


};

#endif // HTCCHARTDATAFILE_H
