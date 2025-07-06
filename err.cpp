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

    DWORD _err = GetLastError( );
    std::string _e = "ERROR: ";
    std::string _m = msg.toStdString() + _e + std::to_string(_err);

    ui->errLBL->setText(_m.c_str());
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

DWORD errs::get_last_error( )
{
    return GetLastError( );
}
