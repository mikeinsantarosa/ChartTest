#include "htcchartdatamangler.h"

HTCChartDataMangler::HTCChartDataMangler(QObject *parent) : QObject(parent)
{

}

void HTCChartDataMangler::Init(QStringList fileList, QVector<int> columns)
{
    _baseFileList = fileList;
    _selectedColumns = columns;

    loadFilesIntoData();
    if (sortFileset())
    {
        discoverRanges();
        discoverStartStopRangeIDs();
        setNumberOfChartsTobuild();
        setColumnLists();
        setFileDelim();
        BuildAllChartDataSets();

        //listDataSets();



        _initialized = true;
        qDebug() << "initialized OK!";
    }




}

bool HTCChartDataMangler::GetItitializedDataOK()
{
    return _initialized;
}



int HTCChartDataMangler::findFirstDataRow(QStringList list, QString delimiter)
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

                if (!dataItem.isEmpty())
                {

                    if(re.exactMatch(dataItem))
                    {

                        numFinds = numFinds + 1;

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



void HTCChartDataMangler::loadFilesIntoData()
{
    if (!_baseFileList.isEmpty())
    {
       for(int i = 0; i < _baseFileList.count(); i++)
       {
           HTCChartDataFile * df = new HTCChartDataFile(_baseFileList.at(i));
           _dataFiles.append(*df);
       }

    }
}

bool HTCChartDataMangler::sortFileset()
{
    bool result = false;

    if(!_dataFiles.isEmpty())
    {
        qSort(_dataFiles.begin(), _dataFiles.end(), [](const HTCChartDataFile& a, const HTCChartDataFile& b) { return a.SortOrderIndex < b.SortOrderIndex; });

        result = true;
    }
}

void HTCChartDataMangler::listFiles()
{
    if(!_baseFileList.isEmpty())
    {
        for(int i = 0; i < _baseFileList.count(); i++)
        {
            qDebug() << "file " << i << " is ->" << _baseFileList.at(i);
        }
    }

}

void HTCChartDataMangler::listDataFiles()
{

    if(!_dataFiles.isEmpty())
    {

        foreach(HTCChartDataFile df, _dataFiles)
        {

            qDebug() << "data file last freq " << df.getOrientationFRange() << " sort order " << df.GetSortOrderIndex();
        }
    }

}

void HTCChartDataMangler::listDataSets()
{
    QStringList target;
    foreach (QStringList list,_dataSets)
    {
        qDebug() << "number of rows " << list.count();

        qDebug() << "row 1 " << list.at(0);
    }

}

void HTCChartDataMangler::listThisList(QStringList list)
{
    for(int i = 0; i < list.count(); i++)
    {
        qDebug() << "List row-"<< i << " - " << list.at(i);
    }

}

void HTCChartDataMangler::discoverRanges()
{

    if(!_rangeList.isEmpty())
    {
        _rangeList.clear();
    }


    if(!_dataFiles.isEmpty())
    {
        foreach(HTCChartDataFile df, _dataFiles)
        {

            QString range = df.getOrientationFRange();
            if(!_rangeList.contains(range))
            {
                _rangeList.append(range);
            }

        }

        _numberOfRanges = _rangeList.count();
    }

}

void HTCChartDataMangler::discoverStartStopRangeIDs()
{
    for(int i = 0; i < _rangeList.count(); i++)
    {
        FileStartIDX[i] = discoverStartRangeID(_rangeList.at(i));
        FileStopIDX[i] = discoverStopRangeID(_rangeList.at(i));
    }

}

int HTCChartDataMangler::discoverStartRangeID(QString range)
{
    int counter = 0;
    int result = -1;

    foreach(HTCChartDataFile df, _dataFiles)
    {

        QString newRange = df.getOrientationFRange();
        if(newRange == range)
        {
            result = counter;
            break;
        }

        counter++;

    }

    return result;
}

int HTCChartDataMangler::discoverStopRangeID(QString range)
{
    int counter = 0;
    int result = -1;
    bool rangeFound = false;
    QString nextRange = "";

    foreach(HTCChartDataFile df, _dataFiles)
    {

        QString newRange = df.getOrientationFRange();

        if(counter ==_dataFiles.count() - 1)
        {
            nextRange = newRange;
            result = counter;
            break;
        }
        else
        {
            HTCChartDataFile  nextDataFile = _dataFiles[counter + 1];
            nextRange = df.getOrientationFRange();

        }

        result = counter;

        if(rangeFound == false)
        {
            if(newRange == range)
            {
                rangeFound = true;
            }


        }
        else if(newRange != range)
        {
            result = counter - 1;
            break;
        }

        counter++;

    }

    return result;
}

void HTCChartDataMangler::setNumberOfChartsTobuild()
{
    if(!_selectedColumns.isEmpty())
    {
        _numberOfChartsToBuild = _selectedColumns.count() - 1;
    }

}

void HTCChartDataMangler::setColumnLists()
{
    QString delim = ",";
    QString columnSet = "";

    if(!_columnSets.isEmpty())
    {
        _columnSets.clear();
    }

    for(int i = 0; i < _selectedColumns.count() - 1; i++)
    {
        columnSet.clear();
        columnSet.append(QString::number(_selectedColumns[0]));
        columnSet.append(delim);
        columnSet.append(QString::number(_selectedColumns[i+1]));

        _columnSets.append(columnSet);
    }

}

void HTCChartDataMangler::setFileDelim()
{
    if(!_dataFiles.isEmpty())
    {
        HTCChartDataFile df = _dataFiles[0];
        _dataFileDelim = df.getFileDelim();
    }

}

void HTCChartDataMangler::BuildAllChartDataSets()
{

   if(!_dataSets.isEmpty())
   {
       _dataSets.clear();
   }

    for(int i = 0; i < _numberOfChartsToBuild; i++)
    {
        QStringList dataset = BuildDataSet(_columnSets.at(i));
       _dataSets.append(dataset);
    }


}

QStringList HTCChartDataMangler::BuildDataSet(QString columns)
{

    QStringList result;

    QString line = "";
    int pos;
    int loop = 0;


    // get the header
    // +++++++++++++++++
    result = getDataSetHeader(columns, FileStartIDX[0], FileStopIDX[0]);

    QStringList buildColumns = columns.split(_dataFileDelim);


    for (int x = 0; x < _numberOfRanges; x++)
    {
        result = getDataChunkByRange(result,columns,x);

    }

    listThisList(result);

    return result;


}

QStringList HTCChartDataMangler::getDataSetHeader(QString columns, int startFileNum, int stopFileNum)
{
    QStringList result;
    QString line = "";
    int pos;

    QStringList buildColumns = columns.split(_dataFileDelim);

    for(int r = startFileNum; r < stopFileNum ; r++)
    {

        HTCChartDataFile df = _dataFiles[r];

        QStringList Hdr = _dataFiles[r].getColumnHeaderList();

        if(r == 0)
        {
            int numberOfBuildColumns = buildColumns.count();
            for(int i = 0; i < numberOfBuildColumns; i++)
            {
                pos = buildColumns.at(i).toInt();
                line.append(Hdr.at(pos));
                line.append(_dataFileDelim);
            }
       }
        else
        {
             int numberOfBuildColumns = buildColumns.count();
             for(int i = 1; i < numberOfBuildColumns; i++)
             {
                 pos = buildColumns.at(i).toInt();
                 line.append(Hdr.at(pos));
                 line.append(_dataFileDelim);
             }
        }



    }
    // do the last column
    QStringList Hdr = _dataFiles[stopFileNum].getColumnHeaderList();
    pos = buildColumns.at(1).toInt();
    line.append(Hdr.at(pos));

    result.append(line);

    return result;


}

QStringList HTCChartDataMangler::getDataChunkByRange(QStringList list, QString columns, int range)
{
    QString line = "";
    int pos;
    QString rowInfo;
    QStringList Hdr;

    //QStringList whatever = list;
    QStringList result = list;



    int StartRangeIDX = FileStartIDX[range];
    HTCChartDataFile df = _dataFiles[StartRangeIDX];
    int lastDataRow = df.getlastDataRowNumber();
    QStringList buildColumns = columns.split(_dataFileDelim);

    for(int rowNum = 0; rowNum < lastDataRow + 1; rowNum++)
    {

        line.clear();
        for(int r = FileStartIDX[range]; r < FileStopIDX[range]; r++)
        {

            HTCChartDataFile df = _dataFiles[r];
            rowInfo = df.GetTableDataByRow(rowNum);
            Hdr = rowInfo.split(_dataFileDelim);

            if(r == 0)
            {

                int numberOfBuildColumns = buildColumns.count();
                for(int i = 0; i < numberOfBuildColumns; i++)
                {
                    pos = buildColumns.at(i).toInt();
                    line.append(Hdr.at(pos));
                    line.append(_dataFileDelim);
                    //qDebug() << "line is now " << line;

                }
           }
            else
            {
                 int numberOfBuildColumns = buildColumns.count();
                 for(int i = 1; i < numberOfBuildColumns; i++)
                 {
                     pos = buildColumns.at(i).toInt();
                     line.append(Hdr.at(pos));
                     line.append(_dataFileDelim);

                     //qDebug() << "line is now " << line;

                 }
            }


        }

        // do the last file
        // ++++++++++++++++++++++++++++++++++++++++++++++++++


        HTCChartDataFile df = _dataFiles[FileStopIDX[range]];
        rowInfo = df.GetTableDataByRow(rowNum);
        Hdr = rowInfo.split(_dataFileDelim);
        pos = buildColumns.at(1).toInt();
        line.append(Hdr.at(pos));

        //qDebug() << "line is now " << line;

        result.append(line);

        //qDebug() << "number of rows is now " << result.count();
        // qDebug() << "bang!";
    }

    return result;



}

