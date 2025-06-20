#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#include <QMainWindow>
#include <QWidget>
#include <QWindow>

#include <windows.h>
#include <psapi.h>

namespace Ui {
class process_handler;
}

class process_handler : public QWidget
{
    Q_OBJECT

public:
    explicit process_handler(QWidget *parent = nullptr);
    ~process_handler();

signals:
    void ph_closed( );
    void send_console( QString msg );

public slots:
    void list_processes( );
    void get_processes ( );
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::process_handler *ui;
};

#endif // PROCESS_HANDLER_H
