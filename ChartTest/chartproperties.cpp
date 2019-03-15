// ++++++++++++++++++++++++++++++++++++++++++++ //
// File: chartproperties.cpp
// Description: Provides controls to
// modify the underlying chart.
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

#include "chartproperties.h"
#include "ui_chartproperties.h"

ChartProperties::ChartProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartProperties)
{
    ui->setupUi(this);
    initPenStyleCombos();

    _busy = true;

    dblValidator = new QDoubleValidator();
    dblValidator->setNotation(QDoubleValidator::ScientificNotation);
    dblValidator->setRange(-9.9E19, 9.9E19,12);
    ui->lineXMin->setValidator(dblValidator);
    ui->lineXMax->setValidator(dblValidator);
    ui->lineYMin->setValidator(dblValidator);
    ui->lineYMin->setValidator(dblValidator);

    // set dialog colors
    // -----------------------------

    _ChartDialogBaseColor = QColor("#E6E3E3");  // E6E3E3 ; #CFCDCD - was BDBCBC
    _ChartSubPanelColor = QColor("#EFEFEF");    // EFEFEF ; #BDBCBC - was CFCDCD

    masterPal.setColor(QPalette::Background, _ChartDialogBaseColor);

    this->setAutoFillBackground(true);
    this->setPalette(masterPal);

    ui->tabWidgetChartProp->setCurrentIndex(0);
    subDialogPal.setColor(QPalette::Background, _ChartSubPanelColor);


    ui->groupPens->setAutoFillBackground(true);
    ui->groupPens->setPalette(subDialogPal);

    ui->groupChartTitle->setAutoFillBackground(true);
    ui->groupChartTitle->setPalette(subDialogPal);

    ui->groupXAxisItems->setAutoFillBackground(true);;
    ui->groupXAxisItems->setPalette(subDialogPal);

    ui->groupYAxisItems->setAutoFillBackground(true);
    ui->groupYAxisItems->setPalette(subDialogPal);



    // set non-sizable control fonts
    _controlsDefaualtFontColor = QColor("#000000");
    _controlsDefaualtFontColorPalette.setColor(QPalette::Text, _controlsDefaualtFontColor);
    _controlsDefaualtPointSize = 10;
    _controlsDefaualtFontName = "Arial"; //Webdings Courier New
    _controlsDefaualtFont.setPointSize(_controlsDefaualtPointSize);
    _controlsDefaualtFont.setFamily(_controlsDefaualtFontName);

    ui->lineXMin->setFont(_controlsDefaualtFont);
    ui->lineXMin->setPalette(_controlsDefaualtFontColorPalette);

    ui->lineXMax->setFont(_controlsDefaualtFont);
    ui->lineXMax->setPalette(_controlsDefaualtFontColorPalette);

    ui->lineYMin->setFont(_controlsDefaualtFont);
    ui->lineYMin->setPalette(_controlsDefaualtFontColorPalette);

    ui->lineYMax->setFont(_controlsDefaualtFont);
    ui->lineYMax->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinXAxisRotation->setFont(_controlsDefaualtFont);
    ui->spinXAxisRotation->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinYAxisRotation->setFont(_controlsDefaualtFont);
    ui->spinYAxisRotation->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinXMajorTics->setFont(_controlsDefaualtFont);
    ui->spinXMajorTics->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinXMinorTics->setFont(_controlsDefaualtFont);
    ui->spinXMinorTics->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinYMajorTics->setFont(_controlsDefaualtFont);
    ui->spinYMajorTics->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinYMinorTics->setFont(_controlsDefaualtFont);
    ui->spinYMinorTics->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinXMajorThickness->setFont(_controlsDefaualtFont);
    ui->spinXMajorThickness->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinXMinorThickness->setFont(_controlsDefaualtFont);
    ui->spinXMinorThickness->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinYMajorThickness->setFont(_controlsDefaualtFont);
    ui->spinYMajorThickness->setPalette(_controlsDefaualtFontColorPalette);

    ui->spinYMinorThickness->setFont(_controlsDefaualtFont);
    ui->spinYMinorThickness->setPalette(_controlsDefaualtFontColorPalette);

    disablePushButtons();

    _busy = false;

}

ChartProperties::~ChartProperties()
{
    delete ui;
}

void ChartProperties::setChartTitleItems(QString title, QFont font, QColor color)
{
    _busy = true;
    QPalette pal;
    pal.setColor(QPalette::Text, color);
    ui->textChartTitleText->setText(title);
    ui->textChartTitleText->setFont(font);
    ui->textChartTitleText->setPalette(pal);




    _busy = false;
}

void ChartProperties::setChartXAxisItems(QString UnitsText, QFont UnitsFont, QBrush UnitsBrush,
                                         QFont LabelFont, QColor LabelColor, double LabelRotation,
                                         double min, double max, QString linlog)
{
    _busy = true;

    ui->txtXAxisLabelText->setText(UnitsText);
    ui->txtXAxisLabelText->setFont(UnitsFont);
    QPalette pX;
    pX.setBrush(QPalette::Text, UnitsBrush);
    ui->txtXAxisLabelText->setPalette(pX);



    ui->txtXLabels->setText("Sample");
    ui->txtXLabels->setFont(LabelFont);
    QPalette pXLabel;
    pXLabel.setColor(QPalette::Text, LabelColor);
    ui->txtXLabels->setPalette(pXLabel);

    ui->lineXMin->setText(QString::number(min));
    ui->lineXMax->setText(QString::number(max));

    ui->spinXAxisRotation->setValue(LabelRotation);
    setLinLogChecked("X", linlog);

    _busy = false;
}

void ChartProperties::setChartXAxisGridLines(bool AxisMajorLinesAreVisible, int AxisMajorLinesTicCount,
                                             QColor AxisMajorLinesColor, double AxisMajorGridLinesize,
                                             bool AxisMinorLinesAreVisible, int AxisMinorLinesTicCount,
                                             QColor AxisMinorLinesColor, double AxisMinorGridLinesize)
{

    ui->checkXMajor->setChecked(AxisMajorLinesAreVisible);
    ui->spinXMajorThickness->setValue(AxisMajorGridLinesize);

    // Set the X Axis Major tic Label color
    // -----------------------------------------------------
    QPalette  palMajor;
    palMajor.setColor(QPalette::Base, Qt::white);
    palMajor.setColor(QPalette::WindowText, AxisMajorLinesColor);
    ui->labelXMajorTics->setPalette(palMajor);

    // Set the X Axis Major spinbox text/count value
    // -----------------------------------------------------
    ui->spinXMajorTics->setValue(AxisMajorLinesTicCount);

    // Set the X Axis Major spin box text color
    // -----------------------------------------------------
    palMajor.setColor(QPalette::Text, AxisMajorLinesColor);
    ui->spinXMajorTics->setPalette(palMajor);


    ui->checkXMinor->setChecked(AxisMinorLinesAreVisible);
    ui->spinXMinorThickness->setValue(AxisMinorGridLinesize);

    // Set the X Axis Minor tic Label color
    // -----------------------------------------------------
    QPalette  palMinor = QPalette();
    palMinor.setColor(QPalette::Base, Qt::white);
    palMinor.setColor(QPalette::WindowText, AxisMajorLinesColor);
    ui->labelXMinorTics->setPalette(palMinor);

    // Set the X Axis Minor spinbox text/count value
    // -----------------------------------------------------
    palMinor.setColor(QPalette::Text, AxisMajorLinesColor);
    ui->spinXMinorTics->setPalette(palMinor);
    ui->spinXMinorTics->setValue(AxisMinorLinesTicCount);

}

void ChartProperties::setChartYAxisItems(QString UnitsText, QFont UnitsFont, QBrush UnitsBrush,
                                         QFont LabelFont, QColor LabelColor, double LabelRotation,
                                         double min, double max, QString linlog)
{
    _busy = true;
    ui->txtYAxisLabelText->setText(UnitsText);
    ui->txtYAxisLabelText->setFont(UnitsFont);
    ui->txtYAxisLabelText->setTextColor(UnitsBrush.color());
    QPalette pY;
    pY.setBrush(QPalette::Text, UnitsBrush);
    ui->txtYAxisLabelText->setPalette(pY);

    ui->txtYLabels->setText("Sample");
    ui->txtYLabels->setFont(LabelFont);
    QPalette pYLabel;
    pYLabel.setColor(QPalette::Text, LabelColor);
    ui->txtYLabels->setPalette(pYLabel);

    ui->lineYMin->setText(QString::number(min));
    ui->lineYMax->setText(QString::number(max));

    ui->spinYAxisRotation->setValue(LabelRotation);
    setLinLogChecked("Y", linlog);

    // tooltips
    setToolTips();

    _busy = false;
}

void ChartProperties::setChartYAxisGridLines(bool AxisMajorLinesAreVisible, int AxisMajorLinesTicCount,
                                             QColor AxisMajorLinesColor, double AxisMajorGridLinesize,
                                             bool AxisMinorLinesAreVisible, int AxisMinorLinesTicCount,
                                             QColor AxisMinorLinesColor, double AxisMinorGridLinesize)
{
    ui->checkYMajor->setChecked(AxisMajorLinesAreVisible);
    ui->spinYMajorThickness->setValue(AxisMajorGridLinesize);

    // Set the X Axis Major tic Label color
    // -----------------------------------------------------
    QPalette  palMajor;
    palMajor.setColor(QPalette::Base, Qt::white);
    palMajor.setColor(QPalette::WindowText, AxisMajorLinesColor);
    ui->labelYMajorTics->setPalette(palMajor);

    // Set the X Axis Major spinbox text/count value
    // -----------------------------------------------------
    ui->spinYMajorTics->setValue(AxisMajorLinesTicCount);

    // Set the X Axis Major spin box text color
    // -----------------------------------------------------
    palMajor.setColor(QPalette::Text, AxisMajorLinesColor);
    ui->spinYMajorTics->setPalette(palMajor);


    ui->checkYMinor->setChecked(AxisMinorLinesAreVisible);
    ui->spinYMinorThickness->setValue(AxisMinorGridLinesize);

    // Set the X Axis Minor tic Label color
    // -----------------------------------------------------
    QPalette  palMinor = QPalette();
    palMinor.setColor(QPalette::Base, Qt::white);
    palMinor.setColor(QPalette::WindowText, AxisMajorLinesColor);
    ui->labelYMinorTics->setPalette(palMinor);

    // Set the X Axis Minor spinbox text/count value
    // -----------------------------------------------------
    palMinor.setColor(QPalette::Text, AxisMajorLinesColor);
    ui->spinYMinorTics->setPalette(palMinor);
    ui->spinYMinorTics->setValue(AxisMinorLinesTicCount);

}

void ChartProperties::setPenItems(int width, QColor color, int penStyle, QString penName, int penNumber)
{
    _busy = true;
    QPalette palPen;

    qDebug() << "assigning values to pen" << penNumber;

    if (penNumber == 1)
    {

        // set pen state
        _penStates[penNumber - 1] = 1;
        bool state = _penStates[penNumber - 1] != 0;

        qDebug() << "This pen state is " << state;

        // Convert color to palette
        palPen.setColor(QPalette::Text, color);
        palPen.setColor(QPalette::Base, Qt::white);

        // update widget colors
        ui->linePen01->setPalette(palPen);
        ui->spinBox01->setPalette(palPen);

        // set pen Name
        ui->linePen01->setText(penName);

        // update pen size control
        ui->spinBox01->setValue(width);

        // update pen style control
        ui->comboPen01->setCurrentIndex(penStyle);

    }
    _busy = false;
}

void ChartProperties::on_btnClose_clicked()
{
    close();
}

void ChartProperties::on_btnChartTitleTextFont_clicked()
{
    QFont font = getNewFont(ui->textChartTitleText->font());
    ui->textChartTitleText->setFont(font);
    emit ChartTitleTextFont(font);
}

QFont ChartProperties::getNewFont(QFont currentFont)
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

QColor ChartProperties::getNewColor(QColor currentColor)
{
    QColor result = currentColor;

    QColor color = QColorDialog::getColor(currentColor, this);
        if( color.isValid() )
        {
          result = color;
        }
        else
        {
            result = currentColor;
        }

        return result;

}

QStringList ChartProperties::getPenTypes()
{
    QStringList result = QStringList() << "NoPen" << "Solid" << "Dash" << "Dot" << "DashDot" << "DashDotDot" << "CustomDash";

    return result;
}

void ChartProperties::initPenStyleCombos()
{
    ui->comboPen01->addItems(getPenTypes());
    ui->comboPen02->addItems(getPenTypes());
    ui->comboPen03->addItems(getPenTypes());
    ui->comboPen04->addItems(getPenTypes());
    ui->comboPen05->addItems(getPenTypes());
    ui->comboPen06->addItems(getPenTypes());
    ui->comboPen07->addItems(getPenTypes());
    ui->comboPen08->addItems(getPenTypes());
    ui->comboPen09->addItems(getPenTypes());
    ui->comboPen10->addItems(getPenTypes());
    ui->comboPen11->addItems(getPenTypes());
    ui->comboPen12->addItems(getPenTypes());
    ui->comboPen13->addItems(getPenTypes());
    ui->comboPen14->addItems(getPenTypes());
    ui->comboPen15->addItems(getPenTypes());
    ui->comboPen16->addItems(getPenTypes());
    ui->comboPen17->addItems(getPenTypes());
    ui->comboPen18->addItems(getPenTypes());
    ui->comboPen19->addItems(getPenTypes());
    ui->comboPen20->addItems(getPenTypes());
    ui->comboPen21->addItems(getPenTypes());
    ui->comboPen22->addItems(getPenTypes());
    ui->comboPen23->addItems(getPenTypes());
    ui->comboPen24->addItems(getPenTypes());

}

void ChartProperties::updatePenItemsAndNotify(int penNumber)
{


    int width = 0;
    QPalette palPen;
    QColor color;
    int penStyle = 0;
    QString penName;

    if (penNumber == 1)
    {

        // get the width
        width = ui->spinBox01->value();;

        // Convert palette to color
        palPen = ui->linePen01->palette();
        color = palPen.color(QPalette::Text);

        //get the pen style
        penStyle = ui->comboPen01->currentIndex();

        // get pen Name
        penName = ui->linePen01->text();

        // update pen style control
        int penNumber = 1;

        emit HTCChartPenValueChanged(width, color, penStyle, penName, penNumber);

    }

    // emit HTCChartPenValueChanged(width, color, penStyle, penName, penNumber);
}

void ChartProperties::disablePushButtons()
{
    // initially disable all pushButtons?
    //_penStates
    //ui->comboPen01->setEnabled(false);
}

void ChartProperties::on_btnChartTitleTextColor_clicked()
{
    QPalette  pal = ui->textChartTitleText->palette();
    QColor currentColor = pal.color(QPalette::Text);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        QPalette newPalette;
        newPalette.setColor(QPalette::Text, color);

        ui->textChartTitleText->setPalette(newPalette);

        emit ChartTitleTextColor(getColorFromPalette(ui->textChartTitleText->palette()));

    }
}

QColor ChartProperties::getColorFromPalette(QPalette pal)
{
    QColor currentColor = pal.color(QPalette::Text);
    return currentColor;
}

QString ChartProperties::getColorStringFromPalette(QPalette pal)
{
    QString result = "";
    QColor currentColor = pal.color(QPalette::Text);
    int r;
    int g;
    int b;
    int a;
    currentColor.getRgb(&r,&g,&b,&a);

    result.append("RGB Color: " + QString::number(r));
    result.append("," + QString::number(g));
    result.append("," + QString::number(b));


    return result;
}

QString ChartProperties::stripCharFromString(QString stripChar, QString Target)
{
    QString result = "";
    result = Target.remove(stripChar);

    return result;
}

void ChartProperties::setLinLogChecked(QString axis, QString mode)
{
    if (axis=="X")
    {
        if (mode == "LIN")
        {
            // set X lin checked
            ui->radioXLin->setChecked(true);
        }
        else
        {
            // set X log checked
            ui->radioXLog->setChecked(true);
        }
    }
    else
        if (mode == "LIN")
        {
            // set Y lin checked
            ui->radioYLin->setChecked(true);
        }
        else
        {
            // set Y log checked
            ui->radioYLog->setChecked(true);
        }

}



void ChartProperties::on_textChartTitleText_textChanged()
{
        if (!_busy)
        {
            QString title = ui->textChartTitleText->toPlainText();
            emit ChartTitleText(title);
        }
}

void ChartProperties::on_btnXAxisLabelfont_clicked()
{
    QFont font = getNewFont(ui->txtXAxisLabelText->font());
    ui->txtXAxisLabelText->setFont(font);
    emit HTCChartXAxisUnitsTextFontChanged(font);

}

void ChartProperties::on_btnYAxisLabelfont_clicked()
{
    QFont font = getNewFont(ui->txtYAxisLabelText->font());
    ui->txtYAxisLabelText->setFont(font);
    emit HTCChartYAxisUnitsTextFontChanged(font);


}

void ChartProperties::on_btnXaxisLabelColor_clicked()
{
    QPalette  pal = ui->txtXAxisLabelText->palette();
    QColor currentColor = pal.color(QPalette::Text);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        QPalette newPalette;
        newPalette.setColor(QPalette::Text, color);

        ui->txtXAxisLabelText->setPalette(newPalette);
        emit HTCChartXAxisUnitsTextColorChanged(getColorFromPalette(ui->txtXAxisLabelText->palette()));

    }
}

void ChartProperties::on_btnXAxisValuesColor_clicked()
{
    QPalette  pal = ui->txtXLabels->palette();
    QColor currentColor = pal.color(QPalette::Text);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        QPalette newPalette;
        newPalette.setColor(QPalette::Text, color);

        ui->txtXLabels->setPalette(newPalette);
        emit HTCChartXAxisLabelsTextColorChanged(this->getColorFromPalette(ui->txtXLabels->palette()));


    }

}

void ChartProperties::on_btnYaxisLabelColor_clicked()
{
    QPalette  pal = ui->txtYAxisLabelText->palette();
    QColor currentColor = pal.color(QPalette::Text);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        QPalette newPalette;
        newPalette.setColor(QPalette::Text, color);

        ui->txtYAxisLabelText->setPalette(newPalette);
        emit HTCChartYAxisUnitsTextColorChanged(this->getColorFromPalette(ui->txtYAxisLabelText->palette()));


    }

}

void ChartProperties::on_btnXAxisValuesFont_clicked()
{
    QFont font = getNewFont(ui->txtXLabels->font());
    ui->txtXLabels->setFont(font);
    emit HTCChartXAxisLabelsTextFontChanged(font);

}

void ChartProperties::on_btnYAxisValuesFont_clicked()
{

    QFont font = getNewFont(ui->txtYLabels->font());
    ui->txtYLabels->setFont(font);
    emit HTCChartYAxisLabelsTextFontChanged(font);

}

void ChartProperties::on_btnYAxisValuesColor_clicked()
{
    QPalette  pal = ui->txtYLabels->palette();
    QColor currentColor = pal.color(QPalette::Text);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        QPalette newPalette;
        newPalette.setColor(QPalette::Text, color);

        ui->txtYLabels->setPalette(newPalette);
        emit HTCChartYAxisLabelsTextColorChanged(this->getColorFromPalette(ui->txtYLabels->palette()));

    }

}

void ChartProperties::on_spinXAxisRotation_valueChanged(int arg1)
{
   if (!_busy)
   {
        emit HTCChartXAxisLabelsTextRotationChanged(arg1);

   }

}

void ChartProperties::on_spinYAxisRotation_valueChanged(int arg1)
{
    if (!_busy)
    {
        emit HTCChartYAxisLabelsTextRotationChanged(arg1);
    }

}



void ChartProperties::on_txtXAxisLabelText_textChanged()
{
    if (!_busy)
    {
        emit HTCChartXAxisUnitsTextChanged(ui->txtXAxisLabelText->toPlainText());

    }

}

void ChartProperties::on_txtYAxisLabelText_textChanged()
{
    if (!_busy)
    {
        emit HTCChartYAxisUnitsTextChanged(ui->txtYAxisLabelText->toPlainText());

    }
}

// TODO:
// Add protection for negative min/max values
// +++++++++++++++++++++++++++++++++++++++++++
void ChartProperties::on_radioYLog_clicked(bool checked)
{
    emit HTCChartYLogChartRequest(checked);
    qDebug() << "Y log Request " << checked;
}


void ChartProperties::on_btnXAxisMajorGridColor_clicked()
{
   if (!_busy)
   {
       // Check the current label color against the new color
       // -------------------------------------------
       QPalette  pal = ui->labelXMajorTics->palette();
       QColor currentColor = pal.color(QPalette::WindowText);

       QColor color = getNewColor(currentColor);

       if (color != currentColor)
       {
           // change the label color
           pal.setColor(QPalette::WindowText, color);
           ui->labelXMajorTics->setPalette(pal);

           // change the spinbox color
           pal.setColor(QPalette::Text, color);
           ui->spinXMajorTics->setPalette(pal);

           // Fire the signal event
           // -------------------------------------------------------------------------------------------------
           emit HTCChartXAxisMajorTicsColorChanged(color);
       }
    }
}

void ChartProperties::on_btnXAxisMinorGridColor_clicked()
{
    if (!_busy)
    {
        // Check the current label color against the new color
        // -------------------------------------------
        QPalette  pal = ui->labelXMinorTics->palette();
        QColor currentColor = pal.color(QPalette::WindowText);

        QColor color = getNewColor(currentColor);

        if (color != currentColor)
        {
            // change the label color
            pal.setColor(QPalette::WindowText, color);
            ui->labelXMinorTics->setPalette(pal);

            // change the spinbox color
            pal.setColor(QPalette::Text, color);
            ui->spinXMinorTics->setPalette(pal);

            // Fire the signal event
            // -------------------------------------------------------------------------------------------------
            emit HTCChartXAxisMinorTicsColorChanged(color);

        }
    }
}

void ChartProperties::on_btnYAxisMajorGridColor_clicked()
{
    // Check the current label color against the new color
    // -------------------------------------------
    QPalette  pal = ui->labelYMajorTics->palette();
    QColor currentColor = pal.color(QPalette::WindowText);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        // change the label color
        pal.setColor(QPalette::WindowText, color);
        ui->labelYMajorTics->setPalette(pal);

        // change the spinbox color
        pal.setColor(QPalette::Text, color);
        ui->spinYMajorTics->setPalette(pal);

        // Fire the signal event
        // -------------------------------------------------------------------------------------------------
        emit HTCChartYAxisMajorTicsColorChanged(this->getColorFromPalette(ui->spinYMajorTics->palette()));
    }

}

void ChartProperties::on_btnYAxisMinorGridColor_clicked()
{
    // Check the current label color against the new color
    // -------------------------------------------
    QPalette  pal = ui->labelYMinorTics->palette();
    QColor currentColor = pal.color(QPalette::WindowText);

    QColor color = getNewColor(currentColor);

    if (color != currentColor)
    {
        // change the label color
        pal.setColor(QPalette::WindowText, color);
        ui->labelYMinorTics->setPalette(pal);

        // change the spinbox color
        pal.setColor(QPalette::Text, color);
        ui->spinYMinorTics->setPalette(pal);

        // Fire the signal event
        // -------------------------------------------------------------------------------------------------
        emit HTCChartYAxisMinorTicsColorChanged(this->getColorFromPalette(ui->spinYMinorTics->palette()));

    }
}


void ChartProperties::on_checkXMinor_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartXMinorTicsEnabledChanged(checked);
    }
}

void ChartProperties::on_checkXMajor_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartXMajorTicsEnabledChanged(checked);
    }
}

void ChartProperties::on_checkYMajor_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartYMajorTicsEnabledChanged(checked);
    }
}

void ChartProperties::on_checkYMinor_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartYMinorTicsEnabledChanged(checked);
    }
}

//void ChartProperties::on_dspinXMajorTics_valueChanged(double arg1)
//{
//    if (!_busy)
//    {
//        if (ui->checkXMajor->isChecked() == true)
//        {
//            emit HTCChartXMajorTicsValueChanged(arg1);
//        }

//    }
//}

//void ChartProperties::on_dspinXMinorTics_valueChanged(double arg1)
//{
//    if (!_busy)
//    {
//        if (ui->checkXMinor->isChecked() == true)
//        {
//            emit HTCChartXMinorTicsValueChanged(arg1);
//        }

//    }
//}

//void ChartProperties::on_dspinYMajorTics_valueChanged(double arg1)
//{
//    if (!_busy)
//    {
//        if (ui->checkYMajor->isChecked() == true)
//        {
//            emit HTCChartYMajorTicsValueChanged(arg1);
//        }

//    }
//}

//void ChartProperties::on_dspinYMinorTics_valueChanged(double arg1)
//{
//    if (!_busy)
//    {
//        if (ui->checkYMinor->isChecked() == true)
//        {
//            emit HTCChartYMinorTicsValueChanged(arg1);
//        }

//    }
//}


void ChartProperties::on_radioXLin_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartXLinChartRequest(checked);
    }
}

// TODO:
// Add protection for negative min/max values
// +++++++++++++++++++++++++++++++++++++++++++
void ChartProperties::on_radioXLog_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartXLogChartRequest(checked);
    }
}


void ChartProperties::on_radioYLin_clicked(bool checked)
{
    if (!_busy)
    {
        emit HTCChartYLinChartRequest(checked);
        qDebug() << "Y lin Request " << checked;
    }
}

void ChartProperties::on_lineXMax_editingFinished()
{
    double value = ui->lineXMax->text().toDouble();
    emit HTCChartXAxisLabelsTextScaleMaxChanged(value);

}

void ChartProperties::on_lineXMin_editingFinished()
{
    double value = ui->lineXMin->text().toDouble();
    emit HTCChartXAxisLabelsTextScaleMinChanged(value);
}

void ChartProperties::on_lineYMin_editingFinished()
{
    double value = ui->lineYMin->text().toDouble();
    emit HTCChartYAxisLabelsTextScaleMinChanged(value);
}

void ChartProperties::on_lineYMax_editingFinished()
{
    double value = ui->lineYMax->text().toDouble();
    emit HTCChartYAxisLabelsTextScaleMaxChanged(value);
}


// maybe pass a control and pen nmumber
// ------------------------------------
void ChartProperties::on_pBttonPen01_clicked()
{
    if (!_busy)
    {
        QPalette  pal = ui->linePen01->palette();
        QColor currentColor = pal.color(QPalette::Text);

        QColor Labelcolor = getNewColor(currentColor);
        QPalette palPen;

        palPen.setColor(QPalette::Text, Labelcolor);
        palPen.setColor(QPalette::Base, Qt::white);


        if (Labelcolor != currentColor)
        {
            ui->linePen01->setPalette(palPen);
            ui->spinBox01->setPalette(palPen);

            updatePenItemsAndNotify(1);

        }
    }


}

void ChartProperties::on_spinBox01_valueChanged(int arg1)
{
    if (!_busy)
    {
        updatePenItemsAndNotify(1);
    }

}

void ChartProperties::on_linePen01_textChanged(const QString &arg1)
{
    //

}

void ChartProperties::on_comboPen01_currentIndexChanged(int index)
{
    if (!_busy)
    {
        updatePenItemsAndNotify(1);
    }
}

void ChartProperties::on_linePen01_editingFinished()
{
    if (!_busy)
    {
        updatePenItemsAndNotify(1);
    }
}

void ChartProperties::setToolTips()
{
    ui->textChartTitleText->setToolTip("Use &lt;br&gt; in the text to start a next line.");

    ui->btnChartTitleTextFont->setToolTip(ui->textChartTitleText->font().toString());
    ui->btnXAxisLabelfont->setToolTip(ui->txtXAxisLabelText->font().toString());
    ui->btnYAxisLabelfont->setToolTip(ui->txtYAxisLabelText->font().toString());
    ui->btnXAxisValuesFont->setToolTip(ui->txtXLabels->font().toString());
    ui->btnYAxisValuesFont->setToolTip(ui->txtYLabels->font().toString());

    ui->btnChartTitleTextColor->setToolTip("Color: " + getColorStringFromPalette(ui->textChartTitleText->palette()));
    ui->btnXaxisLabelColor->setToolTip("Color: " + getColorStringFromPalette(ui->txtXAxisLabelText->palette()));
    ui->btnYaxisLabelColor->setToolTip("Color: " + getColorStringFromPalette(ui->txtYAxisLabelText->palette()));
    ui->btnXAxisValuesColor->setToolTip("Color: " + getColorStringFromPalette(ui->txtXLabels->palette()));
    ui->btnYAxisValuesColor->setToolTip("Color: " + getColorStringFromPalette(ui->txtYLabels->palette()));

    ui->btnXAxisMajorGridColor->setToolTip("Color: " + getColorStringFromPalette(ui->spinXMajorTics->palette()));
    ui->btnXAxisMinorGridColor->setToolTip("Color: " + getColorStringFromPalette(ui->spinXMinorTics->palette()));
    ui->btnYAxisMajorGridColor->setToolTip("Color: " + getColorStringFromPalette(ui->spinYMajorTics->palette()));
    ui->btnYAxisMinorGridColor->setToolTip("Color: " + getColorStringFromPalette(ui->spinYMinorTics->palette()));


}

void ChartProperties::on_spinXMajorThickness_valueChanged(int arg1)
{
    if (!_busy)
    {
        emit HTCChartYMajorThicknessValueChanged(arg1);
    }
}

void ChartProperties::on_spinXMinorThickness_valueChanged(int arg1)
{
    if (!_busy)
    {

        emit HTCChartXMinorThicknessValueChanged(arg1);
    }
}

void ChartProperties::on_spinYMajorThickness_valueChanged(int arg1)
{
    if (!_busy)
    {
        //qDebug() << "just got a new Y Major value of " << arg1;
        emit HTCChartYMajorThicknessValueChanged(arg1);
    }
}

void ChartProperties::on_spinYMinorThickness_valueChanged(int arg1)
{
    if (!_busy)
    {
        //qDebug() << "just got a new Y Minor value of " << arg1;
        emit HTCChartYMinorThicknessValueChanged(arg1);
    }
}


void ChartProperties::on_spinYMajorTics_valueChanged(int arg1)
{
    if (!_busy)
    {
        if (ui->checkYMajor->isChecked() == true)
        {
            emit HTCChartYMajorTicsValueChanged(arg1);
        }
    }
}

void ChartProperties::on_spinYMinorTics_valueChanged(int arg1)
{
    if (!_busy)
    {
        if (ui->checkYMinor->isChecked() == true)
        {
            emit HTCChartYMinorTicsValueChanged(arg1);
        }
    }
}

void ChartProperties::on_spinXMajorTics_valueChanged(int arg1)
{

        if (!_busy)
        {
            if (ui->checkXMajor->isChecked() == true)
            {
                emit HTCChartXMajorTicsValueChanged(arg1);
            }

        }
}

void ChartProperties::on_spinXMinorTics_valueChanged(int arg1)
{

    if (!_busy)
    {
        if (ui->checkXMinor->isChecked() == true)
        {
            emit HTCChartXMinorTicsValueChanged(arg1);
        }
    }
}
