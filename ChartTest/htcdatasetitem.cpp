#include "htcdatasetitem.h"

HTCDataSetItem::HTCDataSetItem()
{
    _model = "Not Set";
    _serial = "Not Set";
    _key = _model + "_" + _serial;
}

HTCDataSetItem::HTCDataSetItem(QString model, QString serial)
{
    _model = model;
    _serial = serial;
    _key = _model + "_" + _serial;
}

QString HTCDataSetItem::GetModel() const
{
    return _model;
}

QString HTCDataSetItem::GetSerial() const
{
    return _serial;
}

QString HTCDataSetItem::GetKey()
{
    return _key;
}

void HTCDataSetItem::SetModel(QString model)
{
    _model = model;
    updateKey();
}

void HTCDataSetItem::SetSerial(QString serial)
{
    _serial = serial;
    updateKey();
}

void HTCDataSetItem::updateKey()
{
    _key = _model + "_" + _serial;
}
