#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QDebug>
#include <QStringList>

#include "htcchartdatafile.h"
#include "datapoint.h"
#include "htcfilelibrary.h"


class DataManager
{
public:

    static DataManager * GetInstance();
    int loadFileSetFromList(QStringList list, QString delim);
    int getNumberOfFiles();
    QVector <HTCChartDataFile> * getFileSet();
    HTCChartDataFile getFile(int atPos);

    // temp troubleshooting function
    void listLoadedFiles();

private:

    // Singleton pieces
    // ------------------------------------------------
    DataManager();

    static DataManager * _instance;
    HTCFileLibrary * _lib;

    QVector <HTCChartDataFile> *  _fileSet;
    QString _fileDelim;
    int _numberOfFiles;

    int initLibrary();





};

#endif // DATAMANAGER_H
