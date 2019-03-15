#ifndef HTCCHART_H
#define HTCCHART_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
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
#include "chartproperties.h"
#include <QPixmap>
#include <QFileDialog>
#include <QPen>
#include <QRegExp>
#include <QString>



// added for a legend test
// Feb-02-2018
// -----------------------------
#include <QtCharts/QLegendMarker>
#include <QtCharts/QXYLegendMarker>
// --------------------------------------



// the file stuff should be in another object
// but we'll do it here for now
// ----------------------------------------------
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QString>

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
    void setFileToOpen(QString fileName);






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


private:
    Ui::HtcChart *ui;
    ChartProperties * cp = new ChartProperties;

    QChartView *chartView;


    void initProperties();
    void initConnects();
    void initChart();

    QString _rawDataFileAndPath;

    void readfileIntoList(QString fileName);
    //QLineSeries * FillListFromFile();


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

    QColor _penColors[24] = {QColor("#FF0000"), QColor("#0000FF"), QColor("#00FF00"), QColor("#FA9EF7"),
                             QColor("#C79EFA"), QColor("#9ECEFA"), QColor("#9EECFA"), QColor("#9EFAE4"),
                             QColor("#AFFA9E"), QColor("#FADD9E"), QColor("#FAA99E"), QColor("#AB5A50"),
                            QColor("#AB8E50"), QColor("#83AB50"), QColor("#50ABA4"), QColor("#506EAB"),
                            QColor("#8A50AB"), QColor("#AB5063"), QColor("#F7B8EF"), QColor("#B8C7F7"),
                           QColor("#89FBFC"), QColor("#C4D05E"), QColor("#DE77F7"), QColor("#DBF777")};


    void setDataFileDelim(QString fileName);

    void setHeaderValues(QStringList list);



    int findFirstNumericRow(QStringList list, QString delimiter);
    void fillSeriesfromList(QLineSeries * series, int dataSet);

    QStringList _masterlist;

    // Chart Title items
    QColor _chartTitleTextColor;
    QFont _chartTitleTextFont;
    QString _chartTitleText;

    // X Axis Label
    QFont _chartXAxisUnitsTextFont;
    QString _chartXAxisUnitsText;
    QBrush _chartXAxisUnitsBrush;
    QColor _chartXAxisLabelColor;
    QFont _chartXAxisLabelFont;
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
    QColor _chartYAxisLabelColor;
    QFont _chartYAxisLabelFont;
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

    int _penStates[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int _penStyles[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int _penWidths[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    QPen defaultChartPenStyle;
    QPen getPenStyle(int style);

    // first run auto discovery
    bool _autoRangesDiscovered;

    void initMinScaleValues(QStringList list);
    void initMaxScaleValues(QStringList list);


    void clearLayout(QLayout *layout);
    void assignChartToProperties();

    QColor GetNewColor(QColor currentColor);
    QFont GetNewFont(QFont currentFont);

    QPen GetNewGirdLinesPen(QColor color, double size, Qt::PenStyle style);

    void setChartTitleTextColor(QColor color);



};

#endif // HTCCHART_H
