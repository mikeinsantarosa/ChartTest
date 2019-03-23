#include "htcchartfolder.h"
#include <QDebug>



HTCChartFolder::HTCChartFolder(QObject *parent) : QObject(parent)
{

}

int HTCChartFolder::init(QString folder, QString extension)
{

    // ++++++++++++++++++++++++++++++++++++++++++++++++
    // check for file count first
    // we might need to protect against too many files
    // ++++++++++++++++++++++++++++++++++++++++++++++++
    int fileCount = CountFiles(folder);


    if(!folder.isEmpty())
    {

        HTCChartDataFile filObj;

        QString itemName = "";
        int result = 0;
        QString model = "";
        QString serial = "";
        QString temp = "";
        //QStringList theseFnameParts;
        QString fNameDelim = "_";
        QString thisSet = "";
        QString thisTag = "";
        //QString fileToLoad = "";
        //QString fileToCheck = "";
        QString nameToTest = "";


        bool found = false;

        QDir recordDir(folder);
        recordDir.setSorting(QDir::Name);

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
            qDebug() << "Checking itemname  -> " << itemName;


            QFileInfo info = QFileInfo(itemName);
            nameToTest = info.fileName();


            if (nameToTest.contains(extension))
            {


                if(nameToTest.contains("q241") || nameToTest.contains("q242") || nameToTest.contains("q243") == true)
                {

                    thisSet.clear();
                    HTCChartDataFile *  filObj = new HTCChartDataFile(itemName);

                    // need to guard against there being a file that
                    // passes inspection but doesn't have any numerical
                    // data in it.

                    if(filObj->getDataSuccessfullyLoaded())
                    {
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

                    }


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

int HTCChartFolder::CountFiles(QString path)
{
    int suma = 0;
    QDir dir(path);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    if(!dir.exists()) {
    return 1;
    }
    QFileInfoList sList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

    foreach(QFileInfo ruta, sList){
    if(ruta.isDir()){
    suma += CountFiles(ruta.path() + "/" + ruta.completeBaseName()+"/");
    }
    suma++;
    }
    return suma;

}
