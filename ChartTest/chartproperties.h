#ifndef CHARTPROPERTIES_H
#define CHARTPROPERTIES_H

#include <QDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <QPalette>
#include <QDoubleValidator>
#include <QRadioButton>
#include <QtWidgets/QTabWidget>


namespace Ui {
class ChartProperties;
}

class ChartProperties : public QDialog
{
    Q_OBJECT

public:
    explicit ChartProperties(QWidget *parent = 0);
    ~ChartProperties();
    void setChartTitleItems(QString title, QFont font, QColor color);

    void setChartXAxisItems(QString UnitsText, QFont UnitsFont, QBrush UnitsBrush,
                            QFont LabelFont, QColor LabelColor, double LabelRotation,
                            double min, double max, QString linlog);

    void setChartXAxisGridLines(bool AxisMajorLinesAreVisible, int AxisMajorLinesTicCount,
                                QColor AxisMajorLinesColor, double AxisMajorGridLinesize,
                                bool AxisMinorLinesAreVisible, int AxisMinorLinesTicCount,
                                QColor AxisMinorLinesColor, double AxisMinorGridLinesize);

    void setChartYAxisItems(QString UnitsText, QFont UnitsFont, QBrush UnitsBrush,
                            QFont LabelFont, QColor LabelColor, double LabelRotation,
                            double min, double max, QString linlog);

    void setChartYAxisGridLines(bool AxisMajorLinesAreVisible, int AxisMajorLinesTicCount,
                                QColor AxisMajorLinesColor, double AxisMajorGridLinesize,
                                bool AxisMinorLinesAreVisible, int AxisMinorLinesTicCount,
                                QColor AxisMinorLinesColor, double AxisMinorGridLinesize);

    void setPenItems(int width, QColor color, int penStyle, QString penName, int penNumber);


signals:
    // Chart Title
    void ChartTitleText(QString title);
    void ChartTitleTextFont(QFont font);
    void ChartTitleTextColor(QColor color);

    // Chart X Axis Units
    void HTCChartXAxisUnitsTextChanged(QString text);
    void HTCChartXAxisUnitsTextFontChanged(QFont font);
    void HTCChartXAxisUnitsTextColorChanged(QColor color);

   // Chart X Axis Labels
    void HTCChartXAxisLabelsTextRotationChanged(qint32 value);
    void HTCChartXAxisLabelsTextFontChanged(QFont font);
    void HTCChartXAxisLabelsTextColorChanged(QColor color);

    // Chart X Axis Scaling
    void HTCChartXAxisLabelsTextScaleMinChanged(double value);
    void HTCChartXAxisLabelsTextScaleMaxChanged(double value);

    void HTCChartXMajorThicknessValueChanged(double arg1);
    void HTCChartXMinorThicknessValueChanged(double arg1);

    void HTCChartXAxisMajorTicsColorChanged(QColor color);
    void HTCChartXAxisMinorTicsColorChanged(QColor color);

    void HTCChartXMajorTicsEnabledChanged(bool checked);
    void HTCChartXMinorTicsEnabledChanged(bool checked);

    void HTCChartXMinorTicsValueChanged(double arg1);
    void HTCChartXMajorTicsValueChanged(double arg1);

    void HTCChartXLogChartRequest(bool checked);
    void HTCChartXLinChartRequest(bool checked);



    // Chart Y Axis Units
    void HTCChartYAxisUnitsTextChanged(QString text);
    void HTCChartYAxisUnitsTextFontChanged(QFont font);
    void HTCChartYAxisUnitsTextColorChanged(QColor color);

    // Chart Y Axis Labels
    void HTCChartYAxisLabelsTextRotationChanged(qint32 value);
    void HTCChartYAxisLabelsTextFontChanged(QFont font);
    void HTCChartYAxisLabelsTextColorChanged(QColor color);

    // Chart Y Axis Scaling
    void HTCChartYAxisLabelsTextScaleMinChanged(double value);
    void HTCChartYAxisLabelsTextScaleMaxChanged(double value);

    void HTCChartYMajorThicknessValueChanged(double arg1);
    void HTCChartYMinorThicknessValueChanged(double arg1);

    void HTCChartYAxisMajorTicsColorChanged(QColor color);
    void HTCChartYAxisMinorTicsColorChanged(QColor color);

    void HTCChartYMajorTicsEnabledChanged(bool checked);
    void HTCChartYMinorTicsEnabledChanged(bool checked);

    void HTCChartYMinorTicsValueChanged(double arg1);
    void HTCChartYMajorTicsValueChanged(double arg1);

    void HTCChartYLogChartRequest(bool checked);
    void HTCChartYLinChartRequest(bool checked);


    void HTCChartPenValueChanged(int width, QColor color, int penStyle, QString penName, int penNumber);

//ChartYAxisLabelTextRotation


private slots:
    void on_btnClose_clicked();

    void on_btnChartTitleTextFont_clicked();

    void on_btnChartTitleTextColor_clicked();

    void on_textChartTitleText_textChanged();

    void on_btnXAxisLabelfont_clicked();

    void on_btnYAxisLabelfont_clicked();

    void on_btnXaxisLabelColor_clicked();

    void on_btnXAxisValuesColor_clicked();

    void on_btnYaxisLabelColor_clicked();

    void on_btnXAxisValuesFont_clicked();

    void on_btnYAxisValuesFont_clicked();

    void on_btnYAxisValuesColor_clicked();

    void on_spinXAxisRotation_valueChanged(int arg1);

    void on_spinYAxisRotation_valueChanged(int arg1);

    void on_txtXAxisLabelText_textChanged();

    void on_txtYAxisLabelText_textChanged();

    void on_radioYLog_clicked(bool checked);

    void on_btnXAxisMajorGridColor_clicked();

    void on_btnXAxisMinorGridColor_clicked();

    void on_btnYAxisMajorGridColor_clicked();

    void on_btnYAxisMinorGridColor_clicked();

    void on_dspinXMajorThickness_valueChanged(double arg1);

    void on_checkXMinor_clicked(bool checked);

    void on_checkXMajor_clicked(bool checked);

    void on_checkYMajor_clicked(bool checked);

    void on_checkYMinor_clicked(bool checked);

    void on_dspinXMajorTics_valueChanged(double arg1);

    void on_dspinXMinorTics_valueChanged(double arg1);

    void on_dspinYMajorTics_valueChanged(double arg1);

    void on_dspinYMinorTics_valueChanged(double arg1);

    void on_radioXLin_clicked(bool checked);

    void on_radioXLog_clicked(bool checked);

    void on_dspinXMinorThickness_valueChanged(double arg1);

    void on_radioYLin_clicked(bool checked);

    void on_dspinYMajorThickness_valueChanged(double arg1);

    void on_dspinYMinorThickness_valueChanged(double arg1);

    void on_lineXMax_editingFinished();

    void on_lineXMin_editingFinished();

    void on_lineYMin_editingFinished();

    void on_lineYMax_editingFinished();


    void on_pBttonPen01_clicked();

    void on_spinBox01_valueChanged(int arg1);

    void on_linePen01_textChanged(const QString &arg1);

    void on_comboPen01_currentIndexChanged(int index);

    void on_linePen01_editingFinished();

private:

    Ui::ChartProperties *ui;

    QPalette masterPal;
    QPalette subDialogPal;
    QColor _ChartDialogBaseColor;
    QColor _ChartSubPanelColor;

    QDoubleValidator *dblValidator;

    bool _busy = true;

    void setToolTips();

    QColor getColorFromPalette(QPalette pal);
    QString getColorStringFromPalette(QPalette pal);
    QString stripCharFromString(QString stripChar, QString Target);

    void setLinLogChecked(QString axis, QString mode);

    // functions
    QFont getNewFont(QFont currentFont);
    QColor getNewColor(QColor currentColor);

    QFont _controlsDefaualtFont;
    int _controlsDefaualtPointSize;
    QString _controlsDefaualtFontName;
    QColor _controlsDefaualtFontColor;
    QPalette _controlsDefaualtFontColorPalette;

    QStringList getPenTypes();
    void initPenStyleCombos();

    int _penStates[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    void updatePenItemsAndNotify(int penNumber);
    void disablePushButtons();

};

#endif // CHARTPROPERTIES_H
