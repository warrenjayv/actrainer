#include "process_handler.h"
#include "ui_process_handler.h"

process_handler::process_handler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::process_handler)
{
    ui->setupUi(this);

    list_processes( );
    
    connect( ui->refreshBTN, &QPushButton::clicked, this, &process_handler::list_processes);
}

process_handler::~process_handler()
{
    delete ui;
}

void process_handler::closeEvent(QCloseEvent *event )
{
    this->hide( );
    emit ph_closed( );
}

void process_handler::list_processes( )
{
    // ui->processLIST->insertItem( ui->processLIST->currentRow(), new QListWidgetItem(tr("whatever"), ui->processLIST ));
     emit send_console( "• obtaining processes list" );

}

void process_handler::get_process_modules( )
{
    DWORD _procids[1024];
    DWORD _cbn;

    if(!EnumProcesses(_procids, sizeof(_procids), &_cbn))
    {
        emit send_console("• failed to enumerate process list");
        return;
    }

    int _procnt = _cbn / sizeof(DWORD);

    for(int i = 0; i < _procnt; i++)
    {
        if (_procids[i] != 0)
        {
            HANDLE _hproc = OpenProcess( PROCESS_ALL_ACCESS, false, _procids[i] );
            if ( _hproc != NULL )
            {
                char _name[MAX_PATH];
                HMODULE _hmod;
                DWORD   _cmod;

                if (! EnumProcessModules(_hproc, &_hmod, sizeof(_hmod), &_cmod))
                {
                    int _s = GetModuleBaseNameA(_hproc, _hmod, (LPSTR) &_name, sizeof(_name) );

                    if (_s > 0)
                    {
                        QString _qs = QString::fromLocal8Bit(_name);
                        ui->processLIST->addItem(_qs);
                    }

                }

            }
        }
    }
}

