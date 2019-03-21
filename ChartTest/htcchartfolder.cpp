#include "htcchartfolder.h"
#include <QDebug>



HTCChartFolder::HTCChartFolder(QObject *parent) : QObject(parent)
{

}

int HTCChartFolder::init(QString folder, QString extension)
{
    if(!folder.isEmpty())
    {

        HTCChartDataFile filObj;

        QString itemName = "";
        int result = 0;
        QString model = "";
        QString serial = "";
        QString temp = "";
        QStringList theseFnameParts;
        QString fNameDelim = "_";

        QString thisSet = "";
        QString thisTag = "";
        QString fileToLoad = "";



        bool found = false;

        QDir recordDir(folder);

        if(! _folderList.isEmpty())
        {
            _folderList.clear();

        }
        if(!_TaggedList.isEmpty())
        {
            _TaggedList.clear();
        }

        if(!_sets.isEmpty())
        {
            _sets.clear();
        }

        QDirIterator it(recordDir, QDirIterator::Subdirectories);


        while (it.hasNext())
        {
            if (!found)
            {
                found = true;

            }

            itemName = it.next();
            // make sure the found file has the correct extension
            if (itemName.contains(extension))
            {
                if(itemName.contains("q241") || itemName.contains("q242") || itemName.contains("q243"))
                {
                    thisSet.clear();
                    QFileInfo file = QFileInfo(itemName);
                    temp = file.fileName();
                    HTCChartDataFile *  filObj = new HTCChartDataFile(itemName);
                    model = filObj->getOrientationEUTModel();
                    serial = filObj->getOrientationEUTSerial();

                    thisSet.append(model);
                    thisSet.append(fNameDelim);
                    thisSet.append(serial);

                    thisTag.append(filObj->getKey());
                    thisTag.append(",");
                    thisTag.append(itemName);

                    //add it to the set if it doesn't exist
                    if(!_sets.contains(thisSet))
                    {
                        _sets.append(thisSet);
                    }

                    _folderList.append(itemName);
                    _TaggedList.append(thisTag);

                    result += 1;

                    thisTag.clear();
                    thisSet.clear();

                    // the filObj got created so delete it
                    delete filObj;
                }

            }



        }

        return result;
    }
}

QStringList HTCChartFolder::GetFolderList()
{
    return _folderList;
}

QStringList HTCChartFolder::GetDataSetNames()
{
    return _sets;
}

QStringList HTCChartFolder::GetTaggedList()
{
    return _TaggedList;
}
