// ++++++++++++++++++++++++++++++++++++++++++++ //
// File: htcchart.cpp
// Description: Draws an analog chart
//
// Date: 2019-03-07
//
// Working on: Connecting slot return
// data to the chart.
//
// TODO: This thing should not process any
// raw data. It should receive an object
// that has a data, headers description, etc
//
// ++++++++++++++++++++++++++++++++++++++++++++ //
#include "htcchart.h"
#include "ui_htcchart.h"

HtcChart::HtcChart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HtcChart)
{
    ui->setupUi(this);

    _firstNumericRow = -1;
    _autoRangesDiscovered = false;
    initConnects();

    //_rawDataFileAndPath = dataFile;
    initProperties();
    // initChart();
}

HtcChart::~HtcChart()
{
    delete cp;
    delete ui;
}

void HtcChart::setFileToOpen(QString fileName, bool RescaleFreq)
{
    _rawDataFileAndPath = fileName;
    reScaleFreqColumn = RescaleFreq;
    readfileIntoList(_rawDataFileAndPath);

    initChart();


   // createPen(45, "Hi-Limit");

}


void HtcChart::on_actionProperties_triggered()
{

    QPoint p = this->pos();
    QSize s = this->frameSize();
    cp->setGeometry(p.x()+s.width()-800, p.y()+50, s.width(), s.height());

    cp->setChartTitleItems(_chartTitleText, _chartTitleTextFont, _chartTitleTextColor);
    cp->setChartXAxisItems(_chartXAxisUnitsText, _chartXAxisUnitsTextFont, _chartXAxisUnitsBrush, _chartXAxisLabelFont, _chartXAxisLabelColor, _chartXAxisLabelRotation, _XAxisMinValue, _XAxisMaxValue, _chartXAxisLinLogScale);
    cp->setChartXAxisGridLines(_chartXAxisMajorGridLinesVisible,_chartXAxisMajorGridLinesCount, _chartXAxisMajorGridLinesColor, _chartXAxisMajorGridLineSize,_chartXAxisMinorGridLinesVisible,_chartXAxisMinorGridLinesCount, _chartXAxisMinorGridLinesColor, _chartXAxisMinorGridLineSize);
    cp->setChartYAxisItems(_chartYAxisUnitsText, _chartYAxisUnitsTextFont, _chartYAxisUnitsBrush, _chartYAxisLabelFont, _chartYAxisLabelColor, _chartYAxisLabelRotation, _YAxisMinValue, _YAxisMaxValue, _chartYAxisLinLogScale);
    cp->setChartYAxisGridLines(_chartYAxisMajorGridLinesVisible,_chartYAxisMajorGridLinesCount, _chartYAxisMajorGridLinesColor, _chartYAxisMajorGridLineSize,_chartYAxisMinorGridLinesVisible,_chartYAxisMinorGridLinesCount, _chartYAxisMinorGridLinesColor, _chartYAxisMinorGridLineSize);

    //cp->setPenItems(defaultPenWidth, defaultPenColor, defaultPenStyle, _currentHeaderList[1], 1);

    // show modal
    cp->setModal(true);
    cp->show();

}

void HtcChart::on_btnClose_clicked()
{
    if (cp != 0)
    {
        cp->close();
    }

    close();


}


// ----------------------------------------------
// The default stuff should maybe be loaded
// from a settings file instead of hard coded
// here.
// ----------------------------------------------
void HtcChart::initProperties()
{
    // Chart Title font
    _chartTitleText = "Simple Linear Example <br> with 3 lines <br> I hope";
    _chartTitleTextFont = QFont("Arial",20, QFont::Normal );
    _chartTitleTextColor = QColor("#000000");


    _chartXAxisUnitsText = "Test Frequency (Hz)";
    _chartXAxisUnitsBrush.setColor(QColor("#000000"));
    _chartXAxisUnitsTextFont = QFont("Arial",20, QFont::Normal);

    _chartXAxisLabelColor = QColor("#000000");
    _chartXAxisLabelFont = QFont("Arial",14, QFont::Normal );
    _chartXAxisLabelRotation = -45;


    _chartXAxisLinLogScale = "LIN";

    _chartXAxisMajorGridLinesVisible = true;
    _chartXAxisMajorGridLinesCount = 11;
    _chartXAxisMinorGridLinesVisible = false;
    _chartXAxisMinorGridLinesCount = 5;
    _chartXAxisMajorGridLinesColor = QColor("#000000");
    _chartXAxisMinorGridLinesColor = QColor("#000000");
    _chartXAxisMajorGridLineSize = 2;
    _chartXAxisMinorGridLineSize = 1;

    _chartXAxisMajorGridLinesPen = GetNewGirdLinesPen(_chartXAxisMajorGridLinesColor, _chartXAxisMajorGridLineSize, Qt::SolidLine);
    _chartXAxisMinorGridLinesPen = GetNewGirdLinesPen(_chartXAxisMinorGridLinesColor, _chartXAxisMinorGridLineSize, Qt::SolidLine);


    _chartYAxisUnitsText = "Correction Factor";
    _chartYAxisUnitsBrush.setColor(QColor("#000000"));
    _chartYAxisUnitsTextFont = QFont("Arial",20, QFont::Normal);

    _chartYAxisLabelFont = QFont("Arial",14, QFont::Normal );
    _chartYAxisLabelColor = QColor("#000000");
    _chartYAxisLabelRotation = 0;

    _chartYAxisLinLogScale = "LIN";

    _chartYAxisMajorGridLinesVisible = true;
    _chartYAxisMajorGridLinesCount = 11;
    _chartYAxisMinorGridLinesVisible = false;
    _chartYAxisMinorGridLinesCount = 5;
    _chartYAxisMajorGridLinesColor = QColor("#000000");
    _chartYAxisMinorGridLinesColor = QColor("#000000");
    _chartYAxisMajorGridLineSize = 2;
    _chartYAxisMinorGridLineSize = 1;

    _chartYAxisMajorGridLinesPen = GetNewGirdLinesPen(_chartYAxisMajorGridLinesColor, _chartYAxisMajorGridLineSize, Qt::SolidLine);
    _chartYAxisMinorGridLinesPen = GetNewGirdLinesPen(_chartYAxisMinorGridLinesColor, _chartYAxisMinorGridLineSize, Qt::SolidLine);

    defaultPenWidth = 2;
    defaultPenColor = QColor(Qt::blue);
    defaultPenStyle = 1;

}

void HtcChart::initConnects()
{
    // Chart Title
    connect(cp,SIGNAL(ChartTitleText(QString)),this,SLOT(ChartTitleText(QString)));
    connect(cp,SIGNAL(ChartTitleTextFont(QFont)),this,SLOT(ChartTitleTextFont(QFont)));
    connect(cp,SIGNAL(ChartTitleTextColor(QColor)),this,SLOT(ChartTitleTextColor(QColor)));

    // Chart X Axis Items
    connect(cp,SIGNAL(HTCChartXAxisUnitsTextChanged(QString)),this,SLOT(HTCChartXAxisUnitsText(QString)));
    connect(cp,SIGNAL(HTCChartXAxisUnitsTextFontChanged(QFont)),this,SLOT(HTCChartXAxisUnitsTextFont(QFont)));
    connect(cp,SIGNAL(HTCChartXAxisUnitsTextColorChanged(QColor)),this,SLOT(HTCChartXAxisUnitsTextColor(QColor)));


    connect(cp,SIGNAL(HTCChartXAxisLabelsTextRotationChanged(qint32)),this,SLOT(HTCChartXAxisLabelsTextRotation(qint32)));
    connect(cp,SIGNAL(HTCChartXAxisLabelsTextFontChanged(QFont)),this,SLOT(HTCChartXAxisLabelsTextFont(QFont)));
    connect(cp,SIGNAL(HTCChartXAxisLabelsTextColorChanged(QColor)),this,SLOT(HTCChartXAxisLabelsTextColor(QColor)));

    connect(cp,SIGNAL(HTCChartXAxisLabelsTextScaleMinChanged(double)),this,SLOT(HTCChartXAxisLabelsTextScaleMin(double)));
    connect(cp,SIGNAL(HTCChartXAxisLabelsTextScaleMaxChanged(double)),this,SLOT(HTCChartXAxisLabelsTextScaleMax(double)));

    connect(cp,SIGNAL(HTCChartXMajorThicknessValueChanged(double)),this,SLOT(HTCChartXMajorThickness(double)));
    connect(cp,SIGNAL(HTCChartXMinorThicknessValueChanged(double)),this,SLOT(HTCChartXMinorThickness(double)));

    connect(cp,SIGNAL(HTCChartXAxisMajorTicsColorChanged(QColor)),this,SLOT(HTCChartXAxisMajorTicsColor(QColor)));
    connect(cp,SIGNAL(HTCChartXAxisMinorTicsColorChanged(QColor)),this,SLOT(HTCChartXAxisMinorTicsColor(QColor)));

    connect(cp,SIGNAL(HTCChartXMinorTicsEnabledChanged(bool)),this,SLOT(HTCChartXMinorTicsEnabled(bool)));
    connect(cp,SIGNAL(HTCChartXMajorTicsEnabledChanged(bool)),this,SLOT(HTCChartXMajorTicsEnabled(bool)));

    connect(cp,SIGNAL(HTCChartXMinorTicsValueChanged(double)),this,SLOT(HTCChartXMinorTicsValue(double)));
    connect(cp,SIGNAL(HTCChartXMajorTicsValueChanged(double)),this,SLOT(HTCChartXMajorTicsValue(double)));

    connect(cp,SIGNAL(HTCChartXLogChartRequest(bool)),this,SLOT(HTCChartXLogChart(bool)));
    connect(cp,SIGNAL(HTCChartXLinChartRequest(bool)),this,SLOT(HTCChartXLinChart(bool)));


    // Chart Y Axis Items
    connect(cp,SIGNAL(HTCChartYAxisUnitsTextChanged(QString)),this,SLOT(HTCChartYAxisUnitsText(QString)));
    connect(cp,SIGNAL(HTCChartYAxisUnitsTextFontChanged(QFont)),this,SLOT(HTCChartYAxisUnitsTextFont(QFont)));
    connect(cp,SIGNAL(HTCChartYAxisUnitsTextColorChanged(QColor)),this,SLOT(HTCChartYAxisUnitsTextColor(QColor)));

    connect(cp,SIGNAL(HTCChartYAxisLabelsTextRotationChanged(qint32)),this,SLOT(HTCChartYAxisLabelsTextRotation(qint32)));
    connect(cp,SIGNAL(HTCChartYAxisLabelsTextFontChanged(QFont)),this,SLOT(HTCChartYAxisLabelsTextFont(QFont)));
    connect(cp,SIGNAL(HTCChartYAxisLabelsTextColorChanged(QColor)),this,SLOT(HTCChartYAxisLabelsTextColor(QColor)));

    connect(cp,SIGNAL(HTCChartYAxisLabelsTextScaleMinChanged(double)),this,SLOT(HTCChartYAxisLabelsTextScaleMin(double)));
    connect(cp,SIGNAL(HTCChartYAxisLabelsTextScaleMaxChanged(double)),this,SLOT(HTCChartYAxisLabelsTextScaleMax(double)));

    connect(cp,SIGNAL(HTCChartYMajorThicknessValueChanged(double)),this,SLOT(HTCChartYMajorThickness(double)));
    connect(cp,SIGNAL(HTCChartYMinorThicknessValueChanged(double)),this,SLOT(HTCChartYMinorThickness(double)));

    connect(cp,SIGNAL(HTCChartYAxisMajorTicsColorChanged(QColor)),this,SLOT(HTCChartYAxisMajorTicsColor(QColor)));
    connect(cp,SIGNAL(HTCChartYAxisMinorTicsColorChanged(QColor)),this,SLOT(HTCChartYAxisMinorTicsColor(QColor)));

    connect(cp,SIGNAL(HTCChartYMinorTicsEnabledChanged(bool)),this,SLOT(HTCChartYMinorTicsEnabled(bool)));
    connect(cp,SIGNAL(HTCChartYMajorTicsEnabledChanged(bool)),this,SLOT(HTCChartYMajorTicsEnabled(bool)));

    connect(cp,SIGNAL(HTCChartYMinorTicsValueChanged(double)),this,SLOT(HTCChartYMinorTicsValue(double)));
    connect(cp,SIGNAL(HTCChartYMajorTicsValueChanged(double)),this,SLOT(HTCChartYMajorTicsValue(double)));

    connect(cp,SIGNAL(HTCChartYLogChartRequest(bool)),this,SLOT(HTCChartYLogChart(bool)));
    connect(cp,SIGNAL(HTCChartYLinChartRequest(bool)),this,SLOT(HTCChartYLinChart(bool)));

    connect(cp,SIGNAL(HTCChartPenValueChanged(int, QColor, int, QString, int)),this,SLOT(HTCChartPenValues(int, QColor, int, QString, int)));
    connect(cp,SIGNAL(HTCCHartAddPenRequest(double, QString)),this,SLOT(HTCCHartNewPen(double, QString)));
}

void HtcChart::initChart()
{
    bool axisXHasBeenAdded = false;
    bool axisYHasBeenAdded = false;
    QString cName = "";


    _chart = new QChart();

    // Chart Title
    // ----------------------------------
    _chart->setTitle(_chartTitleText);
    _chart->setTitleFont(_chartTitleTextFont);
    _chart->setTitleBrush(QBrush(_chartTitleTextColor));
    _chart->legend()->hide();


    for(int dataSet = 1; dataSet < _currentHeaderCount ; dataSet++)
    {



        QLineSeries *_series = new QLineSeries();
        fillSeriesfromList(_series, dataSet);

        cName = StripQuotesFromString(_currentHeaderList[dataSet]);
        _series->setName(StripQuotesFromString(cName));
        //_series->setName(_currentHeaderList[dataSet]);

        //Series pen color & thickness
        QPen SeriesPen(_penColors[dataSet - 1]);
        SeriesPen.setWidth(_penWidths[dataSet - 1]);
        SeriesPen.setStyle(Qt::PenStyle(_penStyles[dataSet - 1]));

        _series->setPen(SeriesPen);
        _chart->addSeries(_series);

        if(!_UpdatingFromProperties)
        {
            cp->setPenItems(_penWidths[dataSet - 1], _penColors[dataSet - 1], defaultPenStyle, _currentHeaderList[dataSet], dataSet);
        }

        if (_chartXAxisLinLogScale == "LIN" )
        {
            QValueAxis *axisX = new QValueAxis();
            axisX->setMin(_XAxisMinValue);
            axisX->setMax(_XAxisMaxValue);
            axisX->setTitleText(_chartXAxisUnitsText);
            axisX->setTitleBrush(_chartXAxisUnitsBrush);
            axisX->setTitleFont(_chartXAxisUnitsTextFont);
            axisX->setLabelFormat("%i");
            axisX->setGridLineVisible(_chartXAxisMajorGridLinesVisible);
            axisX->setTickCount(_chartXAxisMajorGridLinesCount);
            axisX->setGridLinePen(_chartXAxisMajorGridLinesPen);
            axisX->setMinorGridLineVisible(_chartXAxisMinorGridLinesVisible);
            axisX->setMinorTickCount(_chartXAxisMinorGridLinesCount);
            axisX->setMinorGridLinePen(_chartXAxisMinorGridLinesPen);
            axisX->setLabelsColor(_chartXAxisLabelColor);
            axisX->setLabelsFont(_chartXAxisLabelFont);
            axisX->setLabelsAngle(_chartXAxisLabelRotation);


            _chart->addAxis(axisX, Qt::AlignBottom);

            if (axisXHasBeenAdded == false)
            {
                axisX->setVisible(true);
                axisXHasBeenAdded = true;
            }
            else
            {
                axisX->setVisible(false);
            }

            _series->attachAxis(axisX);

        }
        else
        {
            QLogValueAxis *axisX = new QLogValueAxis();
            axisX->setTitleText(_chartXAxisUnitsText);
            axisX->setTitleBrush(_chartXAxisUnitsBrush);
            axisX->setTitleFont(_chartXAxisUnitsTextFont);
            axisX->setLabelFormat("%i");
            axisX->setMin(_XAxisMinValue);
            axisX->setMax(_XAxisMaxValue);
            axisX->setGridLineVisible(_chartXAxisMajorGridLinesVisible);
            axisX->setGridLinePen(_chartXAxisMajorGridLinesPen);
            axisX->setMinorGridLineVisible(_chartXAxisMinorGridLinesVisible);
            axisX->setMinorTickCount(_chartXAxisMinorGridLinesCount);
            axisX->setMinorGridLinePen(_chartXAxisMinorGridLinesPen);
            axisX->setLabelsColor(_chartXAxisLabelColor);
            axisX->setLabelsFont(_chartXAxisLabelFont);
            axisX->setLabelsAngle(_chartXAxisLabelRotation);

            _chart->addAxis(axisX, Qt::AlignBottom);

            if (axisXHasBeenAdded == false)
            {
                axisX->setVisible(true);
                axisXHasBeenAdded = true;
            }
            else
            {
                axisX->setVisible(false);
            }

            _series->attachAxis(axisX);


        }

        // Y Axis values
        // ------------------------------------
        if (_chartYAxisLinLogScale == "LIN")
        {
             QValueAxis *axisY = new QValueAxis();
             axisY->setMax(_YAxisMaxValue);
             axisY->setMin(_YAxisMinValue);
             axisY->setTitleText(_chartYAxisUnitsText);
             axisY->setLabelFormat("%.1f");
             axisY->setTitleBrush(_chartYAxisUnitsBrush);
             axisY->setTitleFont(_chartYAxisUnitsTextFont);
             axisY->setLabelsColor(_chartYAxisLabelColor);
             axisY->setLabelsFont(_chartYAxisLabelFont);
             axisY->setLabelsAngle(_chartYAxisLabelRotation);
             axisY->setGridLineVisible(_chartYAxisMajorGridLinesVisible);
             axisY->setTickCount(_chartYAxisMajorGridLinesCount);
             axisY->setGridLinePen(_chartYAxisMajorGridLinesPen);
             axisY->setMinorGridLineVisible(_chartYAxisMinorGridLinesVisible);
             axisY->setMinorTickCount(_chartYAxisMinorGridLinesCount);
             axisY->setMinorGridLinePen(_chartYAxisMinorGridLinesPen);

             _chart->addAxis(axisY, Qt::AlignLeft);

            if (axisYHasBeenAdded == false)
            {
                axisY->setVisible(true);
                axisYHasBeenAdded = true;
            }
            else
            {
                axisY->setVisible(false);
            }

            _series->attachAxis(axisY);

        }
        else
        {
            QLogValueAxis *axisY = new QLogValueAxis();
            axisY->setTitleText(_chartYAxisUnitsText);
            axisY->setLabelFormat("%.1f");
            axisY->setTitleBrush(_chartYAxisUnitsBrush);
            axisY->setTitleFont(_chartYAxisUnitsTextFont);
            axisY->setLabelsColor(_chartYAxisLabelColor);
            axisY->setLabelsFont(_chartYAxisLabelFont);
            axisY->setLabelsAngle(_chartYAxisLabelRotation);
            axisY->setMax(_YAxisMaxValue);
            axisY->setMin(_YAxisMinValue);
            axisY->setGridLineVisible(_chartYAxisMajorGridLinesVisible);
            axisY->setGridLinePen(_chartYAxisMajorGridLinesPen);
            axisY->setMinorGridLineVisible(_chartYAxisMinorGridLinesVisible);
            axisY->setMinorTickCount(_chartXAxisMinorGridLinesCount);
            axisY->setMinorGridLinePen(_chartYAxisMinorGridLinesPen);

            _chart->addAxis(axisY, Qt::AlignLeft);

            if (axisYHasBeenAdded == false)
            {
                axisY->setVisible(true);
                axisYHasBeenAdded = true;
            }
            else
            {
                axisY->setVisible(false);
            }

            _series->attachAxis(axisY);


        }


    }



    // added for legend test
    // -------------------------
    _chart->legend()->setVisible(true);
    _chart->legend()->setAlignment(Qt::AlignBottom); // Qt::AlignBottom
    _chart->legend()->setBackgroundVisible(true);

    // pos X/Y  size H/W
    //_chart->legend()->setGeometry(QRectF(0, 0, 600, 400));
   // _chart->legend()->setPreferredSize()



    QFont font = _chart->legend()->font();
        font.setPointSize(_legendFontPointSize);
        //font.setFamily("Courier New");
        font.setFamily("Times New Roman");
        _chart->legend()->setFont(font);



        //  Create the cart
    chartView = new QChartView(_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartLayout->addWidget(chartView,0,0);
}

void HtcChart::readfileIntoList(QString fileName)
{
    _masterlist.clear();
    QFile file(fileName);
    setDataFileDelim(fileName);

    QString msg;
    msg.append("Chart built from - ");
    msg.append(fileName);
    ui->statusbar->showMessage(msg);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                _masterlist += in.readLine();
            }
                file.close();
        }

    // set headers
    setHeaderValues(_masterlist);


}

void HtcChart::setDataFileDelim(QString fileName)
{
    QFileInfo info = QFileInfo(fileName);
    QString extension = info.suffix();

    if (extension == "txt")
    {
        _dataFileDelim = "\t";
    }
    else
    {
        _dataFileDelim = ",";
    }

}

void HtcChart::setHeaderValues(QStringList list)
{

    if (!_masterlist.isEmpty())
    {
        _firstNumericRow = findFirstNumericRow(_masterlist, _dataFileDelim);

        QString current;

        current = list[_firstNumericRow - 1];
        if (!_currentHeaderList.isEmpty())
        {
            _currentHeaderList.clear();
        }

        _currentHeaderList = current.split(_dataFileDelim);
        _currentHeaderCount = _currentHeaderList.count();


    }

}

int HtcChart::findFirstNumericRow(QStringList list, QString delimiter)
{
    QStringList group;
    QString current;
    QString dataItem;
    int numFinds;
    bool isNumber;
    int result;
    bool found = false;


    for (int listRow = 0; listRow < list.count(); listRow++)
    {

        if (!found)
        {
            numFinds = 0;
            current = list[listRow];
            group = current.split(delimiter);

            //qDebug() << "checking this string - " << group;

            for (int i = 0; i < group.count(); i++)
            {

                dataItem = group[i];

                //qDebug() << "Value being checked - " << dataItem;


                dataItem = dataItem.trimmed();
                isNumber = false;
                if (dataItem.toDouble(&isNumber))
                {

                    //qDebug() << "That value was a double - " << dataItem;

                    numFinds = numFinds + 1;
                    if (numFinds > 1)
                    {
                        result = listRow;
                        found = true;
                        break;

                    }
                }

            }

        }
        else
        {
            break;
        }


    }
    return result;

}


    // ----------------------------------------------------
    // todo:
    // Make this thing smarter.
    // - find the first numeric row
    //      and use that as the starting point
    //      for the numeric data
    //      If there is no numeric row - fail
    //      at least return something that be
    //      detected to be a faile value.
    //
    // - if the first row is not numeric
    //      check to see if the value can be
    //      used as a series title and
    //      do that here.
    //
    // -----------------------------------------------------


    void HtcChart::fillSeriesfromList(QLineSeries *series, int dataSet)
{


    QStringList group;
    int start;
    double freq;
    double level;

    if (!_masterlist.isEmpty())
    {


        _currentHeaderRow = _firstNumericRow -1;

        if (_firstNumericRow != -1)
        {

            start = _firstNumericRow;
        }
        else
        {
            start = 0;
        }

        for (int i = start; i < _masterlist.count(); i++)
        {
            group = _masterlist[i].split(_dataFileDelim);

            freq = QString(group.at(0)).toDouble()/getFreqRescaleValue();
            level = QString(group.at(dataSet)).toDouble();

            if (_minfreq > freq)
            {
                _minfreq = freq;
            }
            if (_maxfreq < freq)
            {
                _maxfreq = freq;
            }
            if (_minlevel > level)
            {
                _minlevel = level;
            }
            if (_maxlevel < level)
            {
                _maxlevel = level;
            }

            series->append(freq, level);
        }

    }

    if (_autoRangesDiscovered == false)
    {
        _XAxisMinValue= _minfreq;
        _XAxisMaxValue = _maxfreq;
        _YAxisMinValue= _minlevel;
        _YAxisMaxValue = _maxlevel;

        qDebug() << "AutoDiscovered  min/max freq values of " << _minfreq << "/" << _maxfreq;

        _autoRangesDiscovered = true;

    }





    }

    double HtcChart::getFreqRescaleValue()
    {
        if(reScaleFreqColumn == true)
        {
            _XAxisRescaleValue = 1.0e06;
        }
        else
        {
            _XAxisRescaleValue = 1;
        }
    }

    QPen HtcChart::getPenStyle(int style)
    {
        return QPen(penStyles[style]);
    }

    void HtcChart::createPen(double baseValue, QString header)
    {

        QString currentRow;
        int start = _currentHeaderRow +1;

        _currentHeaderList.append(header);

        for (int i = start; i < _masterlist.count(); i++)
        {
           currentRow = _masterlist.at(i);
           currentRow.append(_dataFileDelim);
           currentRow.append(QString::number(baseValue));
           _masterlist[i] = currentRow;

        }

        updateHeaderCount();

        // reload the chart
        clearLayout(ui->chartLayout);
        initChart();

    }

    void HtcChart::updateHeaderCount()
    {
        _currentHeaderCount = _currentHeaderList.count();
    }




void HtcChart::clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
    if(child->layout() != 0)
        clearLayout( child->layout() );
    else if(child->widget() != 0)
     delete child->widget();
        delete child;
    }

}

void HtcChart::assignChartToProperties()
{

}

QColor HtcChart::GetNewColor(QColor currentColor)
{
    QColor result = currentColor;

    QColor color = QColorDialog::getColor(currentColor, this);
       if( color.isValid() )
       {
         result = color;
         // qDebug() << "Color Choosen : " << color.name();
       }

       return result;
}

QFont HtcChart::GetNewFont(QFont currentFont)
{
    QFont result = currentFont;
    bool ok;

        QFont font = QFontDialog::getFont(
                        &ok,
                        currentFont,
                        this,
                        tr("Pick a font") );
        if(font != currentFont)
        {
            result = font;
        }

        return result;
}

QPen HtcChart::GetNewGirdLinesPen(QColor color, double size, Qt::PenStyle style)
{
    QPen result = QPen(QBrush(color), size,style, Qt::SquareCap, Qt::BevelJoin);
    return result;
}

QString HtcChart::StripQuotesFromString(QString wordToStrip)
{
    QString target = "";
    QString result = "";

    result = wordToStrip;

    target.append('"');

    if(wordToStrip.startsWith(target))
     {
            wordToStrip.remove(0,1);
     }
    if(wordToStrip.endsWith(target))
    {
        wordToStrip.remove(wordToStrip.size()-1,1);
    }

    return result;
}




void HtcChart::on_btnSaveImage_clicked()
{
    QPixmap p = chartView->grab();
    QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Images (*.png)"));
    p.save(filename, "PNG");
}


void HtcChart::ChartTitleText(QString title)
{

    if (_chartTitleText != title)
    {
        _chartTitleText = title;
        qDebug() << "New title - " << title;
        clearLayout(ui->chartLayout);
        initChart();
    }


}

void HtcChart::ChartTitleTextFont(QFont font)
{

    if (_chartTitleTextFont != font)
    {
        _chartTitleTextFont = font;
        qDebug() << "New font is - " << font;
        clearLayout(ui->chartLayout);
        initChart();
    }

}

void HtcChart::ChartTitleTextColor(QColor color)
{

    qDebug() << "color Sent to SLOT is - " << color;
    if (_chartTitleTextColor != color)
    {
        _chartTitleTextColor = color;

        clearLayout(ui->chartLayout);
        initChart();
    }

}

void HtcChart::HTCChartXAxisUnitsText(QString text)
{
    //qDebug() << "Text returned from Slot - " << text;
    if (_chartXAxisUnitsText != text)
    {
        _chartXAxisUnitsText =  text;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXAxisUnitsTextFont(QFont font)
{
    //qDebug() << "Font returned from Slot - " << font;
    if (_chartXAxisUnitsTextFont != font)
    {
        _chartXAxisUnitsTextFont = font;
        clearLayout(ui->chartLayout);
        initChart();
    }

}

void HtcChart::HTCChartXAxisUnitsTextColor(QColor color)
{
    //qDebug() << "Color returned from Slot - " << color;
    if (_chartXAxisUnitsBrush.color() != color)
    {
        _chartXAxisUnitsBrush.setColor(color);
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXAxisLabelsTextRotation(qint32 value)
{
    if (_chartXAxisLabelRotation != value)
    {
        _chartXAxisLabelRotation = value;
        qDebug() << "X Axis Rotation returned from Slot - " << _chartXAxisLabelRotation;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXAxisLabelsTextFont(QFont font)
{
    if (_chartXAxisLabelFont != font)
    {
        _chartXAxisLabelFont = font;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXAxisLabelsTextColor(QColor color)
{
    if (_chartXAxisLabelColor != color)
    {
        _chartXAxisLabelColor = color;
        clearLayout(ui->chartLayout);
        initChart();
    }
}


void HtcChart::HTCChartXAxisLabelsTextScaleMin(double value)
{
    QString v1 = QString::number(value);
    QString v2 = QString::number(_XAxisMinValue);
    if (v1 != v2)
    {
        _XAxisMinValue = value;
        clearLayout(ui->chartLayout);
        initChart();
    }

}

void HtcChart::HTCChartXAxisLabelsTextScaleMax(double value)
{
    QString v1 = QString::number(value);
    QString v2 = QString::number(_XAxisMaxValue);
    if (v1 != v2)
    {
        _XAxisMaxValue = value;
        qDebug() << "Changed variable and rebuilt chart";
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXMajorThickness(double arg1)
{
    if (_chartXAxisMajorGridLineSize != arg1)
    {
        _chartXAxisMajorGridLineSize = arg1;
        _chartXAxisMajorGridLinesPen = GetNewGirdLinesPen(_chartXAxisMajorGridLinesColor,
                                                          _chartXAxisMajorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();

    }
}

void HtcChart::HTCChartXMinorThickness(double arg1)
{
    if (_chartXAxisMinorGridLineSize != arg1)
    {
        _chartXAxisMinorGridLineSize = arg1;
        _chartXAxisMinorGridLinesPen = GetNewGirdLinesPen(_chartXAxisMinorGridLinesColor,
                                                          _chartXAxisMinorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();

    }
}

void HtcChart::HTCChartXAxisMajorTicsColor(QColor color)
{
    if(_chartXAxisMajorGridLinesColor != color)
    {
        _chartXAxisMajorGridLinesColor = color;
        _chartXAxisMajorGridLinesPen = GetNewGirdLinesPen(_chartXAxisMajorGridLinesColor,
                                                          _chartXAxisMajorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXAxisMinorTicsColor(QColor color)
{
    if(_chartXAxisMinorGridLinesColor != color)
    {
        _chartXAxisMinorGridLinesColor = color;
        _chartXAxisMinorGridLinesPen = GetNewGirdLinesPen(_chartXAxisMinorGridLinesColor,
                                                          _chartXAxisMinorGridLineSize, Qt::SolidLine);
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXMajorTicsEnabled(bool checked)
{
    if(_chartXAxisMajorGridLinesVisible != checked)
    {
        _chartXAxisMajorGridLinesVisible = checked;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXMinorTicsEnabled(bool checked)
{
    if (_chartXAxisMinorGridLinesVisible != checked)
    {
        _chartXAxisMinorGridLinesVisible = checked;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXMinorTicsValue(double arg1)
{
    int value = static_cast<int>(arg1);
    if(_chartXAxisMinorGridLinesCount != value)
    {
        _chartXAxisMinorGridLinesCount = value;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXMajorTicsValue(double arg1)
{
    int value = static_cast<int>(arg1);
    if (_chartXAxisMajorGridLinesCount != value)
    {
        _chartXAxisMajorGridLinesCount = value;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartXLogChart(bool checked)
{
    //qDebug() << "X Log request value " << checked;
    _chartXAxisLinLogScale = "LOG";
    clearLayout(ui->chartLayout);
    initChart();
}

void HtcChart::HTCChartXLinChart(bool checked)
{
    //qDebug() << "X Lin request value " << checked;
    _chartXAxisLinLogScale = "LIN";
    clearLayout(ui->chartLayout);
    initChart();
}

void HtcChart::HTCChartYAxisUnitsText(QString text)
{
    //qDebug() << "Text returned from Slot - " << text;
    if (_chartYAxisUnitsText != text)
    {
        _chartYAxisUnitsText =  text;
        clearLayout(ui->chartLayout);
        initChart();
    }
}


void HtcChart::HTCChartYAxisUnitsTextFont(QFont font)
{
    //qDebug() << "Font returned from Slot - " << font;
    if (_chartYAxisUnitsTextFont != font)
    {
        _chartYAxisUnitsTextFont = font;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisUnitsTextColor(QColor color)
{
    //qDebug() << "Color returned from Slot - " << color;
    if (_chartXAxisUnitsBrush.color() != color)
    {
        _chartXAxisUnitsBrush.setColor(color);
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisLabelsTextRotation(qint32 value)
{
    if (_chartYAxisLabelRotation != value)
    {
        _chartYAxisLabelRotation = value;
        qDebug() << "Y Axis Rotation returned from Slot - " << _chartYAxisLabelRotation;
        clearLayout(ui->chartLayout);
        initChart();
    }

}

void HtcChart::HTCChartYAxisLabelsTextFont(QFont font)
{
    if (_chartYAxisLabelFont != font)
    {
        _chartYAxisLabelFont = font;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisLabelsTextColor(QColor color)
{
    if (_chartYAxisLabelColor != color)
    {
        _chartYAxisLabelColor = color;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisLabelsTextScaleMin(double value)
{
    QString v1 = QString::number(value);
    QString v2 = QString::number(_YAxisMinValue);
    if (v1 != v2)
    {
        _YAxisMinValue = value;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisLabelsTextScaleMax(double value)
{
    QString v1 = QString::number(value);
    QString v2 = QString::number(_YAxisMaxValue);
    if (v1 != v2)
    {
        _YAxisMaxValue = value;
        clearLayout(ui->chartLayout);
        initChart();
    }

}


void HtcChart::HTCChartYMajorThickness(double arg1)
{
    if (_chartYAxisMajorGridLineSize != arg1)
    {
        _chartYAxisMajorGridLineSize = arg1;
        _chartYAxisMajorGridLinesPen = GetNewGirdLinesPen(_chartYAxisMajorGridLinesColor,
                                                          _chartYAxisMajorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYMinorThickness(double arg1)
{
    if (_chartYAxisMinorGridLineSize != arg1)
    {
        _chartYAxisMinorGridLineSize = arg1;
        _chartXAxisMinorGridLinesPen = GetNewGirdLinesPen(_chartYAxisMinorGridLinesColor,
                                                          _chartYAxisMinorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisMajorTicsColor(QColor color)
{
    if(_chartYAxisMajorGridLinesColor != color)
    {
        _chartYAxisMajorGridLinesColor = color;
        _chartYAxisMajorGridLinesPen = GetNewGirdLinesPen(_chartYAxisMajorGridLinesColor,
                                                          _chartYAxisMajorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYAxisMinorTicsColor(QColor color)
{
    if(_chartYAxisMinorGridLinesColor != color)
    {
        _chartYAxisMinorGridLinesColor = color;
        _chartYAxisMinorGridLinesPen = GetNewGirdLinesPen(_chartYAxisMinorGridLinesColor,
                                                          _chartYAxisMinorGridLineSize, Qt::SolidLine);

        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYMajorTicsEnabled(bool checked)
{
    if(_chartYAxisMajorGridLinesVisible != checked)
    {
        _chartYAxisMajorGridLinesVisible = checked;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYMinorTicsEnabled(bool checked)
{
    if(_chartYAxisMinorGridLinesVisible != checked)
    {
        _chartYAxisMinorGridLinesVisible = checked;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYMinorTicsValue(double arg1)
{
    int value = static_cast<int>(arg1);
    if(_chartYAxisMinorGridLinesCount != value)
    {
        _chartYAxisMinorGridLinesCount = value;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYMajorTicsValue(double arg1)
{
    int value = static_cast<int>(arg1);
    if(_chartYAxisMajorGridLinesCount != value)
    {
        _chartYAxisMajorGridLinesCount = value;
        clearLayout(ui->chartLayout);
        initChart();
    }
}

void HtcChart::HTCChartYLogChart(bool checked)
{

    //qDebug() << "Y Log request value " << checked;
    _chartYAxisLinLogScale = "LOG";
    clearLayout(ui->chartLayout);
    initChart();
}

void HtcChart::HTCChartYLinChart(bool checked)
{
    qDebug() << "Y Lin request value " << checked;
    _chartYAxisLinLogScale = "LIN";
    clearLayout(ui->chartLayout);
    initChart();
}

void HtcChart::HTCChartPenValues(int width, QColor color, int penStyle, QString penName, int penNumber)
{
   _UpdatingFromProperties = true;

    _penStates[penNumber - 1] = 1;
    _penWidths[penNumber - 1] = width;
    _penColors[penNumber - 1] = color;
    _penStyles[penNumber - 1] = penStyle;
    _currentHeaderList[penNumber] = penName;

    clearLayout(ui->chartLayout);
    initChart();

       _UpdatingFromProperties = false;

}

void HtcChart::HTCCHartNewPen(double baseValue, QString header)
{
    createPen(baseValue, header);

}









