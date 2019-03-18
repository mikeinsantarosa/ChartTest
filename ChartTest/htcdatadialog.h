#ifndef HTCDATADIALOG_H
#define HTCDATADIALOG_H

#include <QDialog>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QStandardItemModel>


namespace Ui {
class HtcDataDialog;
}

class HtcDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HtcDataDialog(QWidget *parent = 0);
    ~HtcDataDialog();

    QStringList * getData();
    QStringList * getHeader();

    bool Init(QString filename);
    QString GetDataFileName();

    int GetNumberOfDataRows();
    int GetNumberOfHeaderRows();

    QVector <int> getSelectedColumnsList();


private slots:
    void on_btnClose_clicked();
    void on_tvData_sectionClicked(int Value);

private:
    Ui::HtcDataDialog *ui;

    QStandardItemModel *model;

    QString _dataFileName;
    QString _delimiter;
    QStringList * _rawList;
    QStringList * _listToView;
    QStringList * _FileHeaderList;
    //QStringList _selectedColumnsList;
    QVector <int> _selectedColumnsList;

    int _firstDataRow;
    int _numberOfDataRows;
    int _numberOfHeaderRows;


    QString setDelimiter(QString fName);
    int findFirstDataRow(QString delimiter);

    bool getFileData(QStringList * list);
    int setListToView(QStringList * list);
    int setHeaderList(QStringList * list);

    //QStringList setSelectedColumnsList();
    QVector <int> setSelectedColumnsList();
    QVector <int>  StringToList(QString value, QString del);
    //QVector <int> StringToList(QString value, QString del);
    // test functions:
    void listColumnList();

    bool isValueInList(QString list, QString value, QString del);

    void loadModel();

};

#endif // HTCDATADIALOG_H
