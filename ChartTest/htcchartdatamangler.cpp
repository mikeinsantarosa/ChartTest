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


        //listFiles();
        getMetrics();

        listTheRangeFileStates();

        if( getFileSetStatus())
        {
            BuildAllChartDataSets();
            _initialized = true;
        }
        else
        {
           _initialized = false;
           showBadFileDataMessage("BadFileData");

        }


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
        //qSort(_dataFiles.begin(), _dataFiles.end(), [](const HTCChartDataFile& a, const HTCChartDataFile& b) { return a.SortOrderIndex < b.SortOrderIndex; });
        std::sort(_dataFiles.begin(), _dataFiles.end(), [](const HTCChartDataFile& a, const HTCChartDataFile& b) { return a.SortOrderIndex < b.SortOrderIndex; });
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


    foreach(HTCChartDataSet ds,_dataSets)
    {
        qDebug() << "chart title - " << ds.GetChartTitle();
    }



}

void HTCChartDataMangler::listThisList(QStringList list)
{
    for(int i = 0; i < list.count(); i++)
    {
        qDebug() << "List row-"<< i << " - " << list.at(i);
    }

}

void HTCChartDataMangler::listTheFileStates()
{
    QStringList list;
    for (int x = 0; x < RowCountsPerFile.count(); x++)
    {
        list.clear();
        list = RowCountsPerFile[x];

        for(int i = 0; i < list.count(); i++)
        {
            qDebug() << "List " << x << " file " << i << " state is " << list.at(i) ;
        }
    }

}

void HTCChartDataMangler::listTheRangeFileStates()
{
    for (int i = 0; i < _rangeList.count(); i++ )
    {
        qDebug() << "range " << i << " file count status is " << RowCountsGoodPerRange[i];
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

bool HTCChartDataMangler::getMetrics()
{
    setFilesPerRange();
    setRowCountsStatus();

}

int HTCChartDataMangler::getFileSetStatus()
{
    int result = 1;
    int count = 0;
    for (int i = 0; i < _rangeList.count(); i++)
    {
        if(RowCountsGoodPerRange[i] == 1)
        {
            count++;
        }

    }
    if(count != _rangeList.count())
    {
        result = 0;
    }

    return result;

}

void HTCChartDataMangler::showBadFileDataMessage(QString key)
{
    QMessageBox msgBox;
    QString badRange = "";
    QString badFileName = "";
    int badRageIDX = -1;
    int badFileNumber = -1;


    QString message = "";

    if(key == "BadFileData")
    {
        //find the bad range
        // ------------------------------------------
        for(int i = 0; i < _rangeList.count(); i++)
        if (RowCountsGoodPerRange[i] == 0)
        {
            badRange = _rangeList.at(i);
            badRageIDX = i;
            break;
        }

        // find at least one bad file
        QStringList list = RowCountsPerFile[badRageIDX];

        for (int i = 0; i < list.count(); i++)
        {
            if(list.at(i).toInt() == 0)
            {
                badFileNumber = i;
                badFileName.append(_baseFileList.at(badFileNumber));
                break;
            }
        }

        message.append("Range: ");
        message.append(badRange);
        message.append(" Has a file with an incorrect number of rows. ");
        message.append(" -- in Filename: ");
        message.append(badFileName);

        qDebug() << "Bad File message = " << message;
        msgBox.setText(message);
        msgBox.setInformativeText("Please correct the problem and try again");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
    }

    int ret = msgBox.exec();
    qDebug() << "return is " << ret;

}

void HTCChartDataMangler::setFilesPerRange()
{
    for (int i = 0; i < _rangeList.count(); i++)
    {
        NumFilesPerRange[i] =  getNumberOfFilesPerRange(_rangeList.at(i),i);
    }
}

int HTCChartDataMangler::getNumberOfFilesPerRange(QString range, int rangeID)
{
    int result = 0;
    foreach(HTCChartDataFile df, _dataFiles)
    {
        if(df.getOrientationFRange() == range)
        {
            result++;
        }
    }

    return result;

}

void HTCChartDataMangler::setRowCountsStatus()
{
    for (int i = 0; i < _rangeList.count(); i++)
    {
        RowCountsGoodPerRange[i] =  setRowCountStatusByRange(_rangeList.at(i),i);

    }
}

int HTCChartDataMangler::setRowCountStatusByRange(QString range, int rangeID)
{
    int result = 0;
    int base = 0;
    int next = 0;
    int count = 0;
    int numberOfFiles = NumFilesPerRange[rangeID];

    bool foundRange = false;

    if (!RowCountsPerFile[rangeID].isEmpty())
    {
        RowCountsPerFile[rangeID].clear();
    }
    RowCountsPerFile[rangeID].clear();

    foreach(HTCChartDataFile df, _dataFiles)
    {
        if(df.getOrientationFRange() == range)
        {
            if (!foundRange)
            {
                base = df.getlastDataRowNumber() - df.getFirstDataRowNumber();
                next = base;
                foundRange = true;
                RowCountsPerFile[rangeID].append("1");
                count++;

            }
            else
            {
                next = df.getlastDataRowNumber() - df.getFirstDataRowNumber();

                if (base == next)
                {
                    RowCountsPerFile[rangeID].append("1");
                    count++;
                }
                else
                {
                    RowCountsPerFile[rangeID].append("0");
                }
            }

        }
    }

    if (count == numberOfFiles)
    {
        result = 1;
    }

    return result;
}

void HTCChartDataMangler::BuildAllChartDataSets()
{

   QStringList dataset;

    if(!_dataSets.isEmpty())
   {
       _dataSets.clear();
   }

   for(int i = 0; i < _numberOfChartsToBuild; i++)
    {
       HTCChartDataSet * dset = new HTCChartDataSet();
       dataset = BuildDataSet(_columnSets.at(i));
       dset->SetData(dataset);

       setDataSetProperties(dset, _columnSets.at(i), i);
       testchart = new HtcChart();
       testchart->setChartByDataSet(dset, true);
       testchart->show();

       _dataSets.append(*dset);

   }


   emit ChartDataSetsReady(_dataSets);

}

QStringList HTCChartDataMangler::BuildDataSet(QString columns)
{

    QStringList result;

    result = getDataSetHeader(columns, FileStartIDX[0], FileStopIDX[0], _loadHeaderFromFilePositions);

    QStringList buildColumns = columns.split(_dataFileDelim);


    for (int i = 0; i < _numberOfRanges; i++)
    {
        result = getDataChunkByRange(result,columns,i);

    }

    return result;


}

QStringList HTCChartDataMangler::getDataSetHeader(QString columns, int startFileNum, int stopFileNum, bool LoadFromFilePositions)
{
    QStringList result;
    QString line = "";
    int pos;


    if (LoadFromFilePositions ==  false)
    {
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

    }
    else
    {
        for(int r = startFileNum; r < stopFileNum ; r++)
        {

            HTCChartDataFile df = _dataFiles[r];

            if(r==0)
            {
                line.append("Test Frequency");
                line.append(_dataFileDelim);
            }

            line.append(df.getOrientationTTRotation());
            line.append("_");
            line.append(df.getOrientationPolarity());
            line.append(_dataFileDelim);

        }

        // do last
        HTCChartDataFile df = _dataFiles[stopFileNum];
        line.append(df.getOrientationTTRotation());
        line.append("_");
        line.append(df.getOrientationPolarity());


        result.append(line);

    }

    return result;


}

QStringList HTCChartDataMangler::getDataChunkByRange(QStringList list, QString columns, int range)
{
    QString line = "";
    int pos;
    QString rowInfo;
    QStringList Hdr;
    int offSetStart;

    //QStringList whatever = list;
    QStringList result = list;



    int StartRangeIDX = FileStartIDX[range];
    HTCChartDataFile df = _dataFiles[StartRangeIDX];
    int lastDataRow = df.getlastDataRowNumber() - df.getFirstDataRowNumber();
    //qDebug() << "number of data rows " << lastDataRow;
    QStringList buildColumns = columns.split(_dataFileDelim);

    if (range == 0)
    {
        offSetStart = 0;
    }
    else
    {
        offSetStart = 1;
    }

    for(int rowNum = offSetStart; rowNum < lastDataRow + 1; rowNum++)
    {


        line.clear();
        for(int r = FileStartIDX[range]; r < FileStopIDX[range]; r++)
        {

            HTCChartDataFile df = _dataFiles[r];
            rowInfo = df.GetTableDataByRow(rowNum);
            Hdr = rowInfo.split(_dataFileDelim);

            if(r == FileStartIDX[range])
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
        _lastFreqInList = Hdr.at(0).toDouble();

        // do the last file
        // ++++++++++++++++++++++++++++++++++++++++++++++++++
        HTCChartDataFile df = _dataFiles[FileStopIDX[range]];
        rowInfo = df.GetTableDataByRow(rowNum);
        Hdr = rowInfo.split(_dataFileDelim);
        pos = buildColumns.at(1).toInt();
        line.append(Hdr.at(pos));

        result.append(line);
    }


    return result;



}

void HTCChartDataMangler::setDataSetProperties(HTCChartDataSet *ChartDataSet, QString columns, int chartNumber)
{

    QString chartTitle;
    QStringList columnValues;
    QString yName;
    QString model;
    QString serial;
    //QFileInfo finfo;

    QStringList values;
    int pos;


    HTCChartDataFile df = _dataFiles[0];
    model = df.getOrientationEUTModel();
    serial = df.getOrientationEUTSerial();
    ChartDataSet->SetModel(model);
    ChartDataSet->SetSerial(serial);
    ChartDataSet->SetXAxisScale("LIN");
    ChartDataSet->SetYAxisScale("LIN");

    values = df.getColumnHeaderList();
    columnValues = columns.split(",");
    pos = columnValues.at(1).toInt();
    yName = values.at(pos);
    ChartDataSet->SetYAxisTitle(yName);
    QFileInfo finfo = df.getDataFileInfo();

    ChartDataSet->SetSampleFileName(finfo.fileName());



    ChartDataSet->SetXAxisTitle("Test Frequency (MHz)");

    // set chart title
    chartTitle.append("Radiated Immunity Composite Data ");
    chartTitle.append("<br>");
    chartTitle.append("for :: ");
    chartTitle.append(model);
    chartTitle.append(" - ");
    chartTitle.append(serial);
    chartTitle.append("<br>");
    chartTitle.append(" for ");
    chartTitle.append(yName);
    ChartDataSet->SetChartTitle(chartTitle);



    //yName =



}



