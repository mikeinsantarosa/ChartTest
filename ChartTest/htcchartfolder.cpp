#include "htcchartfolder.h"
#include <QDebug>



HTCChartFolder::HTCChartFolder(QObject *parent) : QObject(parent)
{

}

int HTCChartFolder::init(QString folder, QString extension)
{
    if(!folder.isEmpty())
    {
        QString itemName = "";
        int result = 0;
        QString model = "";
        QString serial = "";
        QString temp = "";
        QStringList theseFnameParts;
        QString fNameDelim = "_";

        QString thisSet;

        bool found = false;
        //fNameDelim
        //_sets


        QDir recoredDir(folder);

        if(! _folderList.isEmpty())
        {
            _folderList.clear();
        }

        if(!_sets.isEmpty())
        {
            _sets.clear();
        }

        QDirIterator it(recoredDir, QDirIterator::Subdirectories);


        while (it.hasNext())
        {
            if (!found)
            {
                found = true;

            }

            itemName = it.next();
            if (itemName.contains(extension))
            {
                thisSet.clear();
                QFileInfo file = QFileInfo(itemName);
                temp = file.fileName();
                theseFnameParts = temp.split(fNameDelim);
                model = theseFnameParts.at(1);
                serial = theseFnameParts.at(2);

                thisSet.append(model);
                thisSet.append(fNameDelim);
                thisSet.append(serial);

                //add it to the set if it doesn't exist
                if(!_sets.contains(thisSet))
                {
                    _sets.append(thisSet);
                }

                _folderList.append(itemName);
                result += 1;
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
