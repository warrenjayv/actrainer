#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#include <QMainWindow>
#include <QWidget>
#include <QWindow>

#include <windows.h>
#include <psapi.h>
#include <winnt.h>

#include "piper.h"
#include "qlistwidget.h"

namespace Ui {
class process_handler;
}

class process_handler : public QWidget
{
    Q_OBJECT

public:
    explicit process_handler(QWidget *parent = nullptr);
    ~process_handler();

    int selectProcId = 0;

signals:
    void ph_closed( );
    void send_console( QString msg );
    void send_report ( QString msg );

public slots:
    void list_processes      ( );
    void list_processesA     ( );
    void get_process_modules  ( HANDLE _proc );
    void get_process_modulesA ( );
    void setprocID           ( QListWidgetItem* item );
    void attach_process      ( );
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::process_handler *ui;
};

#endif // PROCESS_HANDLER_H
