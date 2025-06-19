#include "process_handler.h"
#include "ui_ac3.h"
#include "ui_process_handler.h"

process_handler::process_handler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::process_handler)
{
    ui->setupUi(this);

}

process_handler::~process_handler()
{
    delete ui;
}

void process_handler::closeEvent(QCloseEvent *event )
{
    this->hide();
    emit ph_closed( );
}
