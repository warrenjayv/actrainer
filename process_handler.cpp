#include "process_handler.h"
#include "ui_process_handler.h"

process_handler::process_handler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::process_handler)
{
    ui->setupUi(this);

    list_processes( );

    connect( ui->pushButton, &QPushButton::clicked, this, &process_handler::list_processes);
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

void process_handler::list_processes( )
{
    // ui->processLIST->insertItem( ui->processLIST->currentRow(), new QListWidgetItem(tr("whatever"), ui->processLIST ));
    emit send_console( "obtaining processes list");
}

void process_handler::get_processes( )
{
    DWORD _procids[1024];
    DWORD _cbn;

    if(!EnumProcesses(_procids, sizeof(_procids), &_cbn))
    {

    }
}

