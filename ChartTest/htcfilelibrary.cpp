#include "htcfilelibrary.h"

HTCFileLibrary::HTCFileLibrary(QVector <HTCChartDataFile> * library)
{
    _masterLibrary = library;
    qDebug() << "library size - " << _masterLibrary->size();
    _numberOfFliesLoaded = _masterLibrary->size();
    _dataSets = new QVector <HTCDataSetItem>;
    _numberOfDataSets = getDataSetCount();

    listDataSet();
    qDebug() << "number of data sets - " << _numberOfDataSets;

}

int HTCFileLibrary::GetNumberOfDataSets()
{
    return _numberOfDataSets;
}

QVector<HTCDataSetItem> *HTCFileLibrary::GetDataSets()
{
    return _dataSets;
}

int HTCFileLibrary::getDataSetCount()
{

    int result = 0;

    QString matchModel;
    QString matchSerial;

    for (int i = 0; i < _numberOfFliesLoaded; i++)
    {
        HTCChartDataFile df = _masterLibrary->at(i);

        matchModel = df.getOrientationEUTModel();
        matchSerial = df.getOrientationEUTSerial();

        if (_dataSets->size()<1)
        {
            // no data sets yet so add this one
            HTCDataSetItem * item = new HTCDataSetItem(matchModel, matchSerial);
            _dataSets->append(*item);
        }
        else
        {
            // see if this model & serial exists in the list
            // if it does bail and if not add it.
            bool found = false;

            for (int d = 0; d < _dataSets->size(); d++)
            {
                QString dsModel = _dataSets->at(d).GetModel();
                QString dsSerial = _dataSets->at(d).GetSerial();

                if ((dsModel == matchModel) && (dsSerial == matchSerial))
                {
                    found = true;
                    break;
                }

            }
            if (!found)
            {
                //qDebug() << "found a new one";
                HTCDataSetItem * item = new HTCDataSetItem(matchModel, matchSerial);
                _dataSets->append(*item);
            }
        }
    }

    result = _dataSets->size();

    return result;


}

void HTCFileLibrary::listDataSet()
{
    for (int i = 0; i < _dataSets->size();i++)
    {
        qDebug() << "dataset - " << i << " = " << _dataSets->at(i).GetModel();
    }

}
