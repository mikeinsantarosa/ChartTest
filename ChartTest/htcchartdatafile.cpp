/* ******************************************************************
 * Class: HTCChartDataFile.cpp
 * Purpose: Represent the data from a .csv or .txt file
 * Rev Date: Feb-14-2018
 *
 * TODO:
 * 1st parse the file name to hopefully help with
 * sorting
 * 2st - Load the data into memory for each file.
 *
 *
 *
 *
 *
 *
 *
 *
 ********************************************************************/

#include "htcchartdatafile.h"


HTCChartDataFile::HTCChartDataFile(QString dataFileName)
{
    setDataFileDelim(dataFileName);
    initProperties();
    _dataSuccessfullyLoaded = false;
    _basedOnThisFile = dataFileName;
    _isStandardTestType = 0;

    init();
    setKey();
}

HTCChartDataFile::HTCChartDataFile()
{

}

QVector<DataPoint> HTCChartDataFile::getAllPoints()
{
    return _allPoints;
}

QStringList HTCChartDataFile::getColumnHeaderList()
{
    return _ColumnHeaderlist;

}

bool HTCChartDataFile::getDataSuccessfullyLoaded()
{
    //qDebug() << "getting file loaded as " << _dataSuccessfullyLoaded;
    return _dataSuccessfullyLoaded;

}

int HTCChartDataFile::getFirstDataRowNumber()
{
    return _firstDataRow;
}

int HTCChartDataFile::getlastDataRowNumber()
{
    return _lastDataRow;
}

double HTCChartDataFile::getFirstFreq()
{
    return _firstFreq;
}

double HTCChartDataFile::getLastFreq()
{
    return _lastFreq;
}

int HTCChartDataFile::getColumnHeadersRowNumber()
{
    return _firstDataRow -1;
}


int HTCChartDataFile::getTotalNumberOfRows()
{
    return _rawDataList.count();
}

void HTCChartDataFile::init()
{
    // make sure we stat with a clean set
    // ----------------------------------------
    _allPoints.clear();

    // assume failure
    _dataSuccessfullyLoaded = false;

    _totalNumberOfRows = loadFileIntoList();

    if (_totalNumberOfRows > 0)
    {
       _firstDataRow = findFirstDataRow(_rawDataList, _dataFileDelim);

       // if there is no numerical data, the firstDataRow
       // will be -1. Let's check that here and do something about it
       // before continuing.

       if(_firstDataRow > -1)
       {
           _lastDataRow = setLastDataRow();

           //qDebug() << "found last data row @ " << _lastDataRow;

           _numberOfDataColumns = setColumnHeadersList(_dataFileDelim);
           _fileInfo = QFileInfo(_basedOnThisFile);

           parseFileProperties();
           setFirstFreq();
           setLastFreq();

           loadDataIntoMemory();


       }
       if (_numberOfDataColumns >= 2)
       {
           _dataSuccessfullyLoaded = true;
       }
       else
       {
           _dataSuccessfullyLoaded = false;
       }



    }


}

int HTCChartDataFile::findFirstDataRow(QStringList list, QString delimiter)
{
    QStringList group;
    QString current;
    QString dataItem;
    int numFinds;
    bool isNumber;
    int result = -1;
    bool found = false;
    QRegExp re("^-?\\d*\\.?\\d+");



    for (int listRow = 0; listRow < list.count(); listRow++)
    {

        if (!found)
        {
            numFinds = 0;
            current = list[listRow];
            group = current.split(delimiter);



            for (int i = 0; i < group.count(); i++)
            {

                dataItem = group[i];

                dataItem = dataItem.trimmed();



                isNumber = false;

                //qDebug() << " row / dataItem to chech to be a number is >> " << listRow << " / " << dataItem;

                if (!dataItem.isEmpty())
                {
                    //qDebug() << "Value is not empty";

                    if(re.exactMatch(dataItem))
                    {

                        //qDebug() << "Value is a number";

                        numFinds = numFinds + 1;

                        //qDebug() << "finds = " << numFinds;

                        if (numFinds > 1)
                        {
                            result = listRow;
                            found = true;
                            break;

                        }
                    }


                }

             }

        }
        else
        {
            break;
        }


    }

    return result;
}

int HTCChartDataFile::setLastDataRow()
{
    int result = -1;
    if (_rawDataList.count() > 0)
    {
        result = _rawDataList.count() -1;
    }
    return result;
}

int HTCChartDataFile::loadFileIntoList()
{
    _rawDataList.clear();
    QFile file(_basedOnThisFile);
    QString msg;
    int result = -1;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                _rawDataList += in.readLine();
            }
                file.close();
        }

    if(_rawDataList.count() > 0)
    {
        result = _rawDataList.count();
    }

    return result;

}

int HTCChartDataFile::setColumnHeadersList(QString delim)
{
    QStringList Headers;
    if (_rawDataList.count() > 0)
    {
        QString strHeader = _rawDataList.at(_firstDataRow - 1);
        Headers = strHeader.split(delim);
    }
    _ColumnHeaderlist = Headers;

    return Headers.count();
}

void HTCChartDataFile::parseFileProperties()
{
    QString fname = _fileInfo.fileName();
    setFilenameProperties(fname);


}

void HTCChartDataFile::setDataFileDelim(QString fileName)
{
    QFileInfo info = QFileInfo(fileName);
    QString extension = info.suffix();

    if (extension == "txt")
    {
        _dataFileDelim = "\t";
    }
    else
    {
        _dataFileDelim = ",";
    }


}

int HTCChartDataFile::solveRangeIDX(QString rangeString)
{
    int result = -1;

    // return values for all known standard ranges
    // this does not solve for the custom ranges like:
    // 800M-880M ...
    // ----------------------------------------------


    if (rangeString.contains("80M-1G"))
    {
        result = 0;
    }
    else if (rangeString.contains("1G-2G"))
    {
        result = 1;
    }
    else if (rangeString.contains("1G-6G"))
    {
        result = 1;
    }
    else if (rangeString.contains("2G-27G"))
    {
        result = 2;
    }


    return result;
}

int HTCChartDataFile::solveOrientationIDX(QString polarity, QString rotation)
{
    int result = -1;

    if (polarity == "BL" && rotation == "0")
    {
        result = 0;
    }
    else if (rotation == "0" && polarity == "H")
    {
        result = 1;
    }
    else if (rotation == "0" && polarity == "V")
    {
        result = 2;
    }
    else if (rotation == "90" && polarity == "H")
    {
        result = 3;
    }
    else if (rotation == "90" && polarity == "V")
    {
        result = 4;
    }
    else if (rotation == "180" && polarity == "H")
    {
        result = 5;
    }
    else if (rotation == "180" && polarity == "V")
    {
        result = 6;
    }
    else if (rotation == "270" && polarity == "H")
    {
        result = 7;
    }
    else if (rotation == "270" && polarity == "V")
    {
        result = 8;
    }

    return result;
}

int HTCChartDataFile::setSortOrderIndex()
{
    int result =  -1;

    if (_rangeIDX == 0)
    {
        if (_orientationOrderIDX == 0)
        {
            result = 0;
        }
        else if (_orientationOrderIDX == 1)
        {
            result = 1;
        }
        else if (_orientationOrderIDX == 2)
        {
            result = 2;
        }
        else if (_orientationOrderIDX == 3)
        {
            result = 3;
        }
        else if (_orientationOrderIDX == 4)
        {
            result = 4;
        }
        else if (_orientationOrderIDX == 5)
        {
            result = 5;
        }else if (_orientationOrderIDX == 6)
        {
            result = 6;
        }else if (_orientationOrderIDX == 7)
        {
            result = 7;
        }else if (_orientationOrderIDX == 8)
        {
            result = 8;
        }
    }
    else if (_rangeIDX == 1)
    {
        if (_orientationOrderIDX == 0)
        {
            result = 9;
        }
        else if (_orientationOrderIDX == 1)
        {
            result = 10;
        }
        else if (_orientationOrderIDX == 2)
        {
            result = 11;
        }
        else if (_orientationOrderIDX == 3)
        {
            result = 12;
        }
        else if (_orientationOrderIDX == 4)
        {
            result = 13;
        }
        else if (_orientationOrderIDX == 5)
        {
            result = 14;
        }else if (_orientationOrderIDX == 6)
        {
            result = 15;
        }else if (_orientationOrderIDX == 7)
        {
            result = 16;
        }else if (_orientationOrderIDX == 8)
        {
            result = 17;
        }
    }

        else if (_rangeIDX == 2)
        {
            if (_orientationOrderIDX == 0)
            {
                result = 18;
            }
            else if (_orientationOrderIDX == 1)
            {
                result = 19;
            }
            else if (_orientationOrderIDX == 2)
            {
                result = 20;
            }
            else if (_orientationOrderIDX == 3)
            {
                result = 21;
            }
            else if (_orientationOrderIDX == 4)
            {
                result = 22;
            }
            else if (_orientationOrderIDX == 5)
            {
                result = 23;
            }else if (_orientationOrderIDX == 6)
            {
                result = 24;
            }else if (_orientationOrderIDX == 7)
            {
                result = 25;
            }else if (_orientationOrderIDX == 8)
            {
                result = 26;
            }
    }
    //qDebug() << "orientaionIndex - " << _orientationOrderIDX;

    return result;

}

void HTCChartDataFile::initProperties()
{
    _standardTestRanges.append("80M-1G");
    _standardTestRanges.append("1G-2G");
    _standardTestRanges.append("2G-27G");
    _standardTestRanges.append("1G-6G");
}




void HTCChartDataFile::loadDataIntoMemory()
{
    QString ref;
    QStringList target;
    double freq;
    QString YValue;
    int thisLastRow = _lastDataRow + 1;


    for (int i = _firstDataRow; i < thisLastRow; i++)
    {
        DataPoint * point = new DataPoint;
        ref = _rawDataList.at(i);

        target = ref.split(_dataFileDelim);
        freq = QString(target.at(0)).toDouble();

        point->setFreq(freq);

        for (int i = 1; i < target.count(); i++)
        {
            YValue = target.at(i);
            point->addValue(YValue);
        }

        _allPoints.append(*point);

    }


}

void HTCChartDataFile::setFilenameProperties(QString fName)
{
    QStringList parts = fName.split(_fileNamePartsDelim);

    // If the user didn't include
    // additional _ (underscores)
    // in the model/serial fields
    // there should be 7 fields
    // in the data file names
    // for an RI test.
    //
    // RI base program fixed
    // so that extra underscores
    // can't occur. Mar-26-2018
    //
    // -----------------------------
    int numParts = parts.count();

    QString last = parts.at(numParts - 1);
    QStringList tail = last.split(".");
    _polarity = tail.at(0);

    _ttRotation = parts.at(numParts - 2);
    _fRange = parts.at(numParts - 3);
    _tLevel = parts.at(numParts - 4);
    _eutSerial = parts.at(numParts - 5);

    // the previous must be set first
    _testCode = parts.at(0);
    _rangeIDX = solveRangeIDX(_fRange);
    _orientationOrderIDX = solveOrientationIDX(_polarity, _ttRotation);
    _sortOrderIDX = setSortOrderIndex();
    setStandardTestType(_fRange);


    if (numParts - 6 == 1)
    {
        _eutModel = parts.at(1);
    }
    else
    {
        _eutModel = "UNKNOWN";

    }

    if (_orientationOrderIDX == -1)
    {
        qDebug() << _eutModel << " - " << _eutSerial << " has a bad order index for polarity/rotation " << _polarity << ":" << _ttRotation;
        qDebug() << "for file -> " << _fileInfo.fileName();
    }


}

void HTCChartDataFile::setFirstFreq()
{
    _firstFreq = -100000;
    if (_rawDataList.count() > 0)
   {
       QString rowData = _rawDataList.at(_firstDataRow);
       QStringList values = rowData.split(_dataFileDelim);
       _firstFreq = QString(values.at(0)).toDouble();
   }
}

void HTCChartDataFile::setLastFreq()
{
    _lastFreq = -1;
     if (_rawDataList.count() > 0)
    {
        QString rowData = _rawDataList.at(_lastDataRow);
        QStringList values = rowData.split(_dataFileDelim);
       _lastFreq = QString(values.at(0)).toDouble();
     }
}

void HTCChartDataFile::setStandardTestType(QString rangeString)
{
    _isStandardTestType = 0;


    if(_standardTestRanges.indexOf(rangeString) > -1)
    {
        _isStandardTestType = 1;
    }
    else
    {
        _isStandardTestType = 0;
    }


}

void HTCChartDataFile::setKey()
{
    if(_firstDataRow > -1)
    {
        _SetKey.clear();
        _SetKey.append(_eutModel);
        _SetKey.append(_fileNamePartsDelim);
        _SetKey.append(_eutSerial);
        _SetKey.append(_fileNamePartsDelim);
        _SetKey.append(QString::number(_isStandardTestType));
    }
    else
    {
        _SetKey.clear();
        _SetKey.append("UNKNOWN-NO-DATA");
    }


}

QFileInfo HTCChartDataFile::getDataFileInfo()
{
    return _fileInfo;
}
;
QString HTCChartDataFile::getOrientationPolarity()
{
    return _polarity;
}

QString HTCChartDataFile::getOrientationTTRotation()
{
    return _ttRotation;
}

QString HTCChartDataFile::getOrientationFRange()
{
    return _fRange;
}

QString HTCChartDataFile::getOrientationTLevel()
{
    return _tLevel;
}

QString HTCChartDataFile::getOrientationEUTSerial()
{
    return _eutSerial;
}

QString HTCChartDataFile::getOrientationEUTModel()
{
    return _eutModel;
}

QString HTCChartDataFile::getOrientationTestCode()
{
    return _testCode;
}

int HTCChartDataFile::getOrientationRangeIndex()
{
    return _rangeIDX;
}

int HTCChartDataFile::getOrientationOrderIndex()
{
    return _orientationOrderIDX;
}

QString HTCChartDataFile::getKey()
{
    return _SetKey;
}
