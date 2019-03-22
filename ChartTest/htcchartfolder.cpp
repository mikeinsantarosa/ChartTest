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
    qDebug() << "number of files in that path is " << fileCount;


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
            // qDebug() << "Checking itemname  -> " << itemName;


            QFileInfo info = QFileInfo(itemName);
            nameToTest = info.fileName();

            //qDebug() << "What's being tested -> " << nameToTest;

            if (nameToTest.contains(extension))
            {

                //qDebug() << "Suffix is a match! " ;


                if(nameToTest.contains("q241") || nameToTest.contains("q242") || nameToTest.contains("q243") == true)
                {

                    //qDebug() << "filter says this is a q241 file";

                    thisSet.clear();
                    HTCChartDataFile *  filObj = new HTCChartDataFile(itemName);


                   qDebug() << "File got loaded successfully ->" << filObj->getDataSuccessfullyLoaded();

                    model = filObj->getOrientationEUTModel();
                    serial = filObj->getOrientationEUTSerial();

                    thisSet.append(model);
                    thisSet.append(fNameDelim);
                    thisSet.append(serial);

                    thisTag.append(filObj->getKey());
                    thisTag.append(",");
                    thisTag.append(itemName);

                    // qDebug() << "This key " << thisTag;

                    //add it to the set if it doesn't exist
                    if(!_sets.contains(thisSet))
                    {

                        qDebug() << "Adding a set -> " << thisSet;
                        _sets.append(thisSet);
                    }

                    _folderList.append(itemName);
                    _TaggedList.append(thisTag);

                    result += 1;

                    //qDebug() << "result count is @ " << result;

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
