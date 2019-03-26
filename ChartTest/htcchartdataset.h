#ifndef HTCCHARTDATASET_H
#define HTCCHARTDATASET_H

#include <QObject>
#include <QDebug>
#include <QStringList>

class HTCChartDataSet
{

public:
    explicit HTCChartDataSet(QObject *parent = nullptr);

    void SetData(QStringList data);
    void SetChartTitle(QString title);
    void SetModel(QString model);
    void SetSerial(QString serial);
    void SetXAxisTitle(QString title);
    void SetYAxisTitle(QString title);
    void SetXAxisScale(QString scale);
    void SetYAxisScale(QString scale);
    void SetSampleFileName(QString file);

    QStringList GetData();
    QString GetChartTitle();
    QString GetModel();
    QString GetSerial();
    QString GetXAxisTitle();
    QString GetYAxisTitle();
    QString GetXAxisScale();
    QString GetYAxisScale();
    QString GetSampleFileName();
    bool GetInitializedOK();


signals:

public slots:


private:
    QStringList _data;
    QString _chartTitle;
    QString _model;
    QString _serial;
    QString _xAxisTitle;
    QString _yAxisTitle;
    QString _xAxisScaling = "LIN";
    QString _yAxisScaling = "LIN";
    bool _initializedOK;
    QString _sampleFileName;

    void setInitializedOKState();


};

#endif // HTCCHARTDATASET_H
