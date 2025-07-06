#include "process_handler.h"
#include "ui_process_handler.h"

process_handler::process_handler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::process_handler)
{
    ui->setupUi(this);

    list_processes( );
    
    connect( ui->refreshBTN,  &QPushButton::clicked, this, &process_handler::list_processes);
    connect( ui->processLIST, &QListWidget::itemPressed, this, &process_handler::setprocID);
    connect( ui->attachBTN,   &QPushButton::clicked, this, &process_handler::attach_process);
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
    emit send_console("• obtain process list");
    std::string _list = piper::commandA("tasklist");
    size_t _sz = _list.find("ERROR");
    if (_sz != std::string::npos)
    {
        DWORD _err = GetLastError( );
        qInfo("list processes: %lx", _err);
        return;
    }
    // qInfo("list processes: %s", _list.c_str());
    v2str _v2 = piper::parseTasks( _list );

    for( int i = 0; i < _v2.a.size( ); i++ )
    {
        QString _ls = tr((_v2.a[i] + " " + _v2.b[i]).c_str());
        ui->processLIST->addItem(_ls);

        QListWidgetItem *item = new QListWidgetItem(_ls);
        // qInfo("%s %s", _v2.a[i].c_str(), _v2.b[i].c_str());
    }
}

void process_handler::setprocID (QListWidgetItem *item)
{
    bool _safe = true;
    qDebug() << item->text();
    QString _s = item->text();
    QList<QString> _l = _s.split(" ");
    selectProcId = _l[1].toInt(&_safe);
}

void process_handler::list_processesA( )
{
    emit send_console( "• obtaining processes list" );

    // QString _list = tr(piper::command("tasklist").c_str());
    std::string _list = piper::command("tasklist");
    qInfo("list processes: %s", _list.c_str());
    size_t _sz = _list.find("ERROR");
    if ( _sz != std::string::npos )
    {
        DWORD _err = GetLastError();
        qInfo("list processes: %lx<error>\n%s", _err, _list.c_str());
        return;
    }

    qInfo("command: %s", _list.c_str());
}

void process_handler::get_process_modules( HANDLE _proc )
{
    HMODULE _hmod[1024];
    MODULEINFO _info;
    DWORD   _cmod;

    if ( !EnumProcessModules(_proc, _hmod, sizeof(_hmod), &_cmod))
    {
        emit send_report("failed to obtain modules.");
        return;
    }

    uint32_t len = _cmod / sizeof(_hmod);

    for(uint32_t i = 0; i < len; i++)
    {
        TCHAR _name[MAX_PATH];
        if ( !GetModuleFileNameEx(_proc, _hmod[i], _name, sizeof(_name)/sizeof(TCHAR)))
        {
            emit send_report("failed to obtain a module.");
            continue;
        }

        if (GetModuleInformation(_proc, _hmod[i], &_info, sizeof(_info)))
        {
            QString _mm = piper::tchar_to_char(_name);

            char _b[MAX_PATH]; sprintf(_b, "%s", _info.lpBaseOfDll);
            QString _mn = tr(_b);

            char _a[MAX_PATH]; sprintf(_a, "%x", _info.lpBaseOfDll);
            QString _ma = tr(_a);

            QString _out = _mm + " " + _mn + " " + _ma;

            qDebug() << _out;

        }
    }
}

void process_handler::get_process_modulesA( )
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
                    emit send_report("unable to enumerate process modules. ");
                    return;
                }

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


void process_handler::attach_process ( )
{
    // [0] attach
    HANDLE _proc = OpenProcess( PROCESS_ALL_ACCESS, false, (DWORD) selectProcId );

    if (_proc == NULL )
    {
        send_report("failed to attach process. ");
        return;
    }

    // [1] get modules
    get_process_modules( _proc );

}
