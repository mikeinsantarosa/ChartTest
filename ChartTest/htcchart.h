#ifndef HTCCHART_H
#define HTCCHART_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QXYLegendMarker>
#include <QPen>
#include <QCategoryAxis>
#include <QChart>
#include <QLineSeries>
#include <QDebug>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLogValueAxis>
#include <QColor>
#include <QColorDialog>
#include <QFontDialog>
#include <QFont>
#include <QBoxLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QPen>
#include <QRegExp>
#include <QString>


#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QString>
#include "htcchartdataset.h"
#include "chartproperties.h"


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class HtcChart;
}

class HtcChart : public QMainWindow
{
    Q_OBJECT

public:
    //explicit HtcChart(QWidget *parent = 0);
    explicit HtcChart(QWidget *parent = 0);
    ~HtcChart();

    QColor ChartTitleTextColor();
    QFont ChartTitleTextFont();
    void setFileToOpen(QString fileName, bool RescaleFreq);
    void setChartByDataSet(HTCChartDataSet * ds, bool RescaleFreq);






private slots:
    void on_actionProperties_triggered();

    void on_btnClose_clicked();

    void on_btnSaveImage_clicked();

    // Chart Title
    void ChartTitleText(QString title);
    void ChartTitleTextFont(QFont font);
    void ChartTitleTextColor(QColor color);

    // Chart X Axis Units
    void HTCChartXAxisUnitsText(QString text);
    void HTCChartXAxisUnitsTextFont(QFont font);
    void HTCChartXAxisUnitsTextColor(QColor color);

    // Chart X Axis Labels
    void HTCChartXAxisLabelsTextRotation(qint32 value);
    void HTCChartXAxisLabelsTextFont(QFont font);
    void HTCChartXAxisLabelsTextColor(QColor color);

    // Chart X Scaling
    void HTCChartXAxisLabelsTextScaleMin(double value);
    void HTCChartXAxisLabelsTextScaleMax(double value);

    void HTCChartXMajorThickness(double arg1);
    void HTCChartXMinorThickness(double arg1);

    void HTCChartXAxisMajorTicsColor(QColor color);
    void HTCChartXAxisMinorTicsColor(QColor color);

    void HTCChartXMajorTicsEnabled(bool checked);
    void HTCChartXMinorTicsEnabled(bool checked);

    void HTCChartXMinorTicsValue(double arg1);
    void HTCChartXMajorTicsValue(double arg1);

    void HTCChartXLogChart(bool checked);
    void HTCChartXLinChart(bool checked);





    // Chart Y Axis Units
    void HTCChartYAxisUnitsText(QString text);
    void HTCChartYAxisUnitsTextFont(QFont font);
    void HTCChartYAxisUnitsTextColor(QColor color);

    // Chart Y Axis Labels
    void HTCChartYAxisLabelsTextRotation(qint32 value);
    void HTCChartYAxisLabelsTextFont(QFont font);
    void HTCChartYAxisLabelsTextColor(QColor color);

    // Chart Y Scaling
    void HTCChartYAxisLabelsTextScaleMin(double value);
    void HTCChartYAxisLabelsTextScaleMax(double value);

    void HTCChartYMajorThickness(double arg1);
    void HTCChartYMinorThickness(double arg1);

    void HTCChartYAxisMajorTicsColor(QColor color);
    void HTCChartYAxisMinorTicsColor(QColor color);

    void HTCChartYMajorTicsEnabled(bool checked);
    void HTCChartYMinorTicsEnabled(bool checked);

    void HTCChartYMinorTicsValue(double arg1);
    void HTCChartYMajorTicsValue(double arg1);

    void HTCChartYLogChart(bool checked);
    void HTCChartYLinChart(bool checked);

    void HTCChartPenValues(int width, QColor color, int penStyle, QString penName, int penNumber);
    void HTCCHartNewPen(double baseValue, QString header);


private:
    Ui::HtcChart *ui;
    ChartProperties * cp = new ChartProperties;

    QChartView *chartView;

    HTCChartDataSet *_dataSet;


    void initProperties();
    void initConnects();
    void initChart();

    QString _rawDataFileAndPath;

    void readfileIntoList(QString fileName);
    void listTheList(QStringList list);

    int _firstNumericRow;
    int _currentHeaderRow;
    QStringList _currentHeaderList;
    QChart *_chart;
    QLineSeries *_series;
    int _currentHeaderCount;
    QString _dataFileDelim;

    double _minfreq = 9999999999;
    double _maxfreq = -9999999999;

    double _minlevel = 9999999999;
    double _maxlevel = -9999999999;


    void setDataFileDelim(QString fileName);
    void setHeaderValues(QStringList list);
    int findFirstNumericRow(QStringList list, QString delimiter);
    void fillSeriesfromList(QLineSeries * series, int dataSet);



    QStringList _masterlist;

    // Chart Title items
    QColor _chartTitleTextColor;
    QFont _chartTitleTextFont;
    QString _chartTitleText;
    int _chartTitleFontSize = 16;

    // X Axis Label
    QFont _chartXAxisUnitsTextFont;
    QString _chartXAxisUnitsText;
    QBrush _chartXAxisUnitsBrush;
    int _chartXAxisUnitsFontSize = 16;
    QColor _chartXAxisLabelColor;
    QFont _chartXAxisLabelFont;
    int _chartXAxisLabelFontSize = 14;
    // rotation was double
    int _chartXAxisLabelRotation;
    QString _chartXAxisLinLogScale;

    // X Axis grid Lines
    bool _chartXAxisMajorGridLinesVisible;
    int  _chartXAxisMajorGridLinesCount;
    bool _chartXAxisMinorGridLinesVisible;
    int  _chartXAxisMinorGridLinesCount;
    QColor _chartXAxisMajorGridLinesColor;
    QColor _chartXAxisMinorGridLinesColor;
    double _chartXAxisMajorGridLineSize;
    double _chartXAxisMinorGridLineSize;
    QPen _chartXAxisMajorGridLinesPen;
    QPen _chartXAxisMinorGridLinesPen;



    // Y Axis Label
    //QColor _chartYAxisUnitsTextColor;
    QFont _chartYAxisUnitsTextFont;
    QString _chartYAxisUnitsText;
    QBrush _chartYAxisUnitsBrush;
    int _chartYAxisUnitsFontSize = 16;
    QColor _chartYAxisLabelColor;
    QFont _chartYAxisLabelFont;
    int _chartYAxisLabelFontSize = 14;
    int _chartYAxisLabelRotation;
    QString _chartYAxisLinLogScale;

    // Y Axis grid Lines
    bool _chartYAxisMajorGridLinesVisible;
    int  _chartYAxisMajorGridLinesCount;
    bool _chartYAxisMinorGridLinesVisible;
    int  _chartYAxisMinorGridLinesCount;
    QColor _chartYAxisMajorGridLinesColor;
    QColor _chartYAxisMinorGridLinesColor;
    double _chartYAxisMajorGridLineSize;
    double _chartYAxisMinorGridLineSize;
    QPen _chartYAxisMajorGridLinesPen;
    QPen _chartYAxisMinorGridLinesPen;



    // X Axis Scaling
    double _XAxisMinValue;
    double _XAxisMaxValue;
    double _XAxisRescaleValue;
    bool reScaleFreqColumn = false;

    double getFreqRescaleValue();

    // Y Axis Scaling
    double _YAxisMinValue;
    double _YAxisMaxValue;

    // pen color
    int defaultPenWidth;
    QString _defaultPenName = "Pen 01";
    QColor defaultPenColor;
    QString penStyles[7] = { "Qt::NoPen",
                             "Qt::SolidLine",
                             "Qt::DashLine",
                             "Qt::DotLine",
                             "Qt::DashDotLine",
                             "Qt::DashDotDotLine",
                             "Qt::CustomDashLine" };
    int defaultPenStyle;

    // Max 15 pens
    QColor _penColors[15] = {QColor("#FF0000"), QColor("#0000FF"), QColor("#2fc50a"), QColor("#f57900"),
                             QColor("#E61994"), QColor("#4e9a06"), QColor("#204a87"), QColor("#5c3566"),
                             QColor("#8f5902"), QColor("#FADD9E"), QColor("#FAA99E"), QColor("#AB5A50"),
                            QColor("#AB8E50"), QColor("#83AB50"), QColor("#50ABA4")};


    int _penStates[15] = { 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0 };
    int _penStyles[15] = { 1, 1, 1, 1, 1, 1, 1, 1,
                           1, 1, 1, 1, 1, 1, 1 };
    int _penWidths[15] = { 3, 1, 1, 1, 1, 1, 1, 1,
                           1, 1, 1, 1, 1, 1, 1 };

    QPen defaultChartPenStyle;
    QPen getPenStyle(int style);
    int _legendFontPointSize = 10;

   void createPen(double baseValue, QString header);
   void updateHeaderCount();


    // first run auto discovery
    bool _autoRangesDiscovered;
    bool _UpdatingFromProperties = false;

    void initMinScaleValues(QStringList list);
    void initMaxScaleValues(QStringList list);


    void clearLayout(QLayout *layout);
    void assignChartToProperties();

    QColor GetNewColor(QColor currentColor);
    QFont GetNewFont(QFont currentFont);

    QPen GetNewGirdLinesPen(QColor color, double size, Qt::PenStyle style);

    void setChartTitleTextColor(QColor color);

    QString StripQuotesFromString(QString wordToStrip);



};

#endif // HTCCHART_H
