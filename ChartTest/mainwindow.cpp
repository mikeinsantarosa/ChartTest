#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chart Selector");
    this->setAttribute(Qt::WA_DeleteOnClose);
   // ui->lineColor->setText("#000088");




}

MainWindow::~MainWindow()
{
    delete ui;

    if (!testchart ==0)
    {
        delete testchart;
    }

    if (!dd == 0)
    {
        delete dd;
    }

}

void MainWindow::on_btnLogGraph_clicked()
{
    // show log graph
    logGraph = new LogGraph;
    logGraph->show();

    qDebug() << "Executed the LOG show() command ";

}

void MainWindow::on_btnCustomGraph_clicked()
{
    // show custom graph
    linGraph = new LinearGraph;
    linGraph->show();

    qDebug() << "Executed the LIN show() command ";


}


void MainWindow::on_btnClose_clicked()
{
    if (testchart == NULL)
    {
       qDebug() << "the textChart was not NULL";
        delete testchart;
       //testchart->close();
    }


    close();

}

void MainWindow::on_btnShowTestChart_clicked()
{
    //QString fileToOpen = "C:/qtTraining/ChartTest/80M-1G_3_h.txt";
    //QString fileToOpen = "/home/mandbx/Desktop/misc-docs/q241/samples/80M-1G_3_h-LOG.txt";
    QString fileToOpen = "/home/mandbx/Desktop/misc-docs/q241/samples/80M-1G_3_h-LOG-10_data_Points.txt";

    testchart = new HtcChart;

    testchart->setFileToOpen(fileToOpen, ui->checkRescaleFreqs->checkState());
    qDebug() << "Loaded file >> " << fileToOpen;

    // load the file and convert to Qlist

    // determin X & Y min & max values

    // Load list into chart




    testchart->show();
}


void MainWindow::on_btnOpenFolders_clicked()
{
    // linux
    // ------------
    QString searchPath = "/home/mandbx/Desktop/misc-docs/q241/Data/";
    // windows
    // -------------
    //QString searchPath = "C:/Users/mpurtell/Desktop/q241/";

    QString extension = ".csv";
    QStringList list;

    QString dir = QFileDialog::getExistingDirectory(this, tr("Select a folder to Load files from..."), searchPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

   // int numberOfFiles = loadListFromPath(dir, extension);


    cdf =  new HTCChartFolder();
    cdf->init(dir, extension);
    list = cdf->GetDataSetNames();

    QString msg;
    ui->listWidgetResults->clear();
    msg.append("Found ");
    msg.append(QString::number(cdf->GetFolderList().count()));
    msg.append(" files  and ");
    msg.append(QString::number(list.count()));
    msg.append(" set(s)");
    ui->listWidgetResults->addItem(msg);
    for(int i = 0; i < list.count(); i++)
    {
        msg.clear();
        msg.append(list.at(i));
        ui->listWidgetResults->addItem(msg);
    }


}





//    if (numberOfFiles > 0)
//    {
//        QStringList fList = getListToLoad();


//        if (fList.count() == numberOfFiles)
//        {
//            dm = DataManager::GetInstance();


//            QString delim = getDelimToUse(fList.at(0));


//            dm->loadFileSetFromList(fList, delim);
//        }
//    }
//}

//void MainWindow::on_btnChangeDate_clicked()
//{
//    QString dt = ui->lineDate->text();
//    QString yr = ui->lineYears->text();
//    QStringList group = dt.split(" ");
//    int newYear = (QString(group[2]).trimmed()).toInt();

//    int yearToAdd = QString(yr).toInt();

//    newYear = newYear + yearToAdd;
//    ui->lineDateResult->setText(QString::number(newYear));
//    qDebug() << "newYear after add " << newYear;

//    QString DueYearString = (QString(group[0]).trimmed() + " " + QString(group[1]).trimmed() + " " + QString::number(newYear));

//   qDebug() << "new date - " << DueYearString;


//}

QStringList MainWindow::getListToLoad()
{
    QStringList result;
    result.clear();

    int numEntries = ui->lstFolders->count();

    for (int i = 0; i < numEntries; i++)
    {
        result.append(ui->lstFolders->item(i)->text());
    }

    return result;
}

QString MainWindow::getDelimToUse(QString fName)
{
    QString result = " "; //default == space

    if (fName.contains(".csv"))
    {
        result = ",";
    }
    else
    {
        if (fName.contains(".txt"))
        {
            result = "/t";
        }
    }
    return result;
}

void MainWindow::listFiles(QStringList * flist, QDir directory, QString indent, QString fExtension)
{
    QString target;
    QDir dir(directory);

    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(QFileInfo finfo, list)
    {
        if (!finfo.isDir() )
        {

            target = finfo.fileName();
            if (target.contains(fExtension))
            {
                //FullFileName = finfo.absoluteFilePath();
                flist->append(finfo.absoluteFilePath());
                ui->lstFolders->addItem(target);
            }
        }
        if (finfo.isDir()) {
                    listFiles(flist, QDir(finfo.absoluteFilePath()), indent, fExtension);
            }
    }



}

int MainWindow::loadListFromPath(QString dir, QString fileExtension)
{
    QString itemName = "";
    int result = 0;

    bool found = false;
    QString delim = ",";

    QDir recoredDir(dir);

    // flush the current list
    // if it looks like we'll
    // be refilling it.
    // -----------------------
    if (recoredDir.count() > 0)
    {
        ui->lstFolders->clear();
    }

    QDirIterator it(recoredDir, QDirIterator::Subdirectories);


    while (it.hasNext())
    {
        if (!found)
        {
            found = true;

        }

        itemName = it.next();
        if (itemName.contains(fileExtension))
        {
             ui->lstFolders->addItem(itemName);
             result += 1;
        }

    }

    return result;
}

QString MainWindow::setDataFileDelim(QString fileName)
{
    QString dataFileDelim = "";

    QFileInfo info = QFileInfo(fileName);
    QString extension = info.suffix();

    if (extension == "txt")
    {
        dataFileDelim = "\t";
    }
    else
    {
        dataFileDelim = ",";
    }

    return dataFileDelim;
}

void MainWindow::initDialogConnects()
{
    connect(dd,SIGNAL(ColumnSelected()),this,SLOT(ColumnSelectedByUser()));
}


void MainWindow::on_btnShowTable_clicked()
{
    HTCTableViewer *tv = new HTCTableViewer(this);
    tv->show();
}

void MainWindow::on_btnLoadFile_clicked()
{
    bool success;
    dd = new HtcDataDialog(this);

    initDialogConnects();
    // linux data file
    // ----------------------------------------------------------------------------------------------------------
    QString fname = "/home/mandbx/Desktop/misc-docs/q241/Data/80M-1G/q241_N9040B_US00091117_3vm_80M-1G_0_BL.csv";

    // Windows file
    //-----------------------------------------------------------------------------------------------------------
    //QString fname = "C:/Users/mpurtell/Desktop/q241/80M-1G/q241_N9029AV05 & E8257DV05_US53250010 & SGX 150_3vm_80M-1G_0_EXTRA-COLUMNS.csv";
    success = dd->Init(fname);

    if (success)
    {


        dd->show();
    }
    else
    {
        qDebug() << "Falied to load data";
    }



}

void MainWindow::on_btnTutorial_clicked()
{

   QString fileToOpen = "/home/mandbx/Desktop/misc-docs/q241/samples/80M-1G_3_h-LOG-2_data_Points.txt";

   QString delim = setDataFileDelim(fileToOpen);



   if(!delim.isEmpty())
   {
       df = new HTCChartDataFile(fileToOpen, delim);
   }

   QStringList list = df->getColumnHeaderList();

   for(int i = 0; i < list.count(); i++)
   {
       qDebug() << "header item-" << i << " == " << list.at(i);
   }

   //qDebug() << " found this model number in the file" << df->getOrientationEUTModel();


}

void MainWindow::ColumnSelectedByUser()
{

    qDebug() << "I got a column click event from the dialog";
    QVector<int> list = dd->getSelectedColumnsList();

   for(int i = 0;i < list.count(); i++)
   {
       qDebug() << "The list has " << list.at(i);
   }

}







void MainWindow::on_btnTest_clicked()
{
    QList<QLabel *> butts = ui->centralWidget->findChildren<QLabel *>();

    foreach(QLabel * label, butts)
    {
         qDebug() << "label name " << label->objectName();
         label->setText("Font set to 20");
         label->setFont(_formLabelFont);
         QString setto = label->font().family();
         qDebug() << "font family set to " << setto;
    }

    qDebug() << "done";
}
