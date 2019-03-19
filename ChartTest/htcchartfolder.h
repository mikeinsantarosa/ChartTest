#ifndef HTCCHARTFOLDER_H
#define HTCCHARTFOLDER_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>



class HTCChartFolder : public QObject
{
    Q_OBJECT
public:
    explicit HTCChartFolder(QObject *parent = nullptr);

    int init(QString folder, QString extension);
    QStringList GetFolderList();
    QStringList GetDataSetNames();

signals:

public slots:

private:

    int _numberOfFiles;
    QStringList _folderList;
    QStringList _sets;



};

#endif // HTCCHARTFOLDER_H
