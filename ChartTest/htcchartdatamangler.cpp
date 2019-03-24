#include "htcchartdatamangler.h"

HTCChartDataMangler::HTCChartDataMangler(QObject *parent) : QObject(parent)
{
    _initialized = true;
}

void HTCChartDataMangler::Init(QStringList fileList, QVector<int> columns)
{
    _baseFileList = fileList;
    //QStringList _headerList;
    _selectedColumns = columns;
    // listFiles();

    loadFilesIntoData();
    listDataFiles();
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

int HTCChartDataMangler::setLastDataRow()
{
    //
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

        qSort(_dataFiles.begin(), _dataFiles.end(), [](const HTCChartDataFile& a, const HTCChartDataFile& b) { return a.SortOrderIndex < b.SortOrderIndex; });

        foreach(HTCChartDataFile df, _dataFiles)
        {

            //qDebug() << "data file last freq " << df.getOrientationFRange() << " sort order " << df.GetSortOrderIndex();
        }
    }

}
