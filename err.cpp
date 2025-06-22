#include "err.h"
#include "ui_err.h"

errs::errs( QWidget *parent) : QWidget(parent), ui(new Ui::errs)
{
    ui->setupUi(this);
}
