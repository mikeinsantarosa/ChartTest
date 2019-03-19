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

        bool found = false;
        QString delim = ",";

        QDir recoredDir(folder);

        if(! _folderList.isEmpty())
        {
            _folderList.clear();
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
