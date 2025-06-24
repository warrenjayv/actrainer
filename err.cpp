#include "err.h"
#include "ui_err.h"

errs::errs( QWidget *parent, QString msg) : QWidget(parent), ui(new Ui::errs)
{
    ui->setupUi(this);
    ui->errLBL->setText(msg);
    connect(ui->okBTN, &QPushButton::clicked, this, &errs::ok);
}

void errs::report( QString msg )
{
    this->show();
    ui->errLBL->setText(msg);
}

void errs::closeEvent(QCloseEvent *event)
{
    this->hide();
}

void errs::ok( )
{
    this->hide();
}

errs::~errs( )
{
    delete ui;
}
