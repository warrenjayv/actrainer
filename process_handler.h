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

private:
    Ui::process_handler *ui;
};

#endif // PROCESS_HANDLER_H
