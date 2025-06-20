#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#include <QMainWindow>
#include <QWidget>
#include <QWindow>

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

public slots:
    void list_processes( );
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::process_handler *ui;
};

#endif // PROCESS_HANDLER_H
