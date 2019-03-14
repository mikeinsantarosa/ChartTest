#include "loggraphnew.h"
#include "ui_loggraphnew.h"

LoggraphNew::LoggraphNew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggraphNew)
{
    ui->setupUi(this);
}

LoggraphNew::~LoggraphNew()
{
    delete ui;
}
