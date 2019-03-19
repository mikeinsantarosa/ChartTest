/* ******************************************************************
 *  Class: DataManager.cpp
 *  Purpose: Singleton pattern, Manages data for the chart builder
 *  Rev Date: Feb-14-2018
 *
 *  TODO:
 *
 *
 *
 *
 *
 *
 *
 *
 *
 ********************************************************************/

#include "datamanager.h"

DataManager* DataManager::_instance = 0;

DataManager *DataManager::GetInstance()
{
    if (_instance == 0)
    {
        _instance = new DataManager();


    }
    return _instance;
}

QVector<HTCChartDataFile> * DataManager::getFileSet()
{
    return _fileSet;

}

HTCChartDataFile DataManager::getFile(int atPos)
{
    if (atPos > -1 && atPos < _numberOfFiles)
    {
        return _fileSet->at(atPos);
    }
}

DataManager::DataManager()
{
    // empty constructor
    //qDebug() << "Initialized DataManager";
}

int DataManager::initLibrary()
{
    _lib = new HTCFileLibrary(_fileSet);

}

void DataManager::listLoadedFiles()
{
    // not sure what this is for?
    //HTCChartDataFile df;
    int numberOfFiles = _fileSet->count();
    for (int i = 0; i < numberOfFiles; i++)
    {
        //df = _fileSet->at(i);
       //
    }



}



// needs translation to HTCDatafile type
int DataManager::loadFileSetFromList(QStringList list, QString delim)
{

    _fileSet = new QVector <HTCChartDataFile> ;
    int result = 0;

    _fileDelim = delim;

    if (list.count() > 0)
    {


        for (int i = 0; i < list.count(); i++)
        {
            HTCChartDataFile * df = new HTCChartDataFile(list.at(i));

            _fileSet->append(*df);
        }

    }

    _numberOfFiles = _fileSet->count();

    if (_numberOfFiles > 0)
    {
       int count = initLibrary();

    }

    return _numberOfFiles;


}
