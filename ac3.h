#ifndef AC3_H
#define AC3_H

#include <QMainWindow>
#include <QSlider>

#include "process_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ac3;
}
QT_END_NAMESPACE

class ac3 : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool is_proc_window NOTIFY notify_proc_window)

public:
    ac3(QWidget *parent = nullptr);
    ~ac3();

signals:
    void set_process     ( );

public slots:
    void attach_process    ( );
    void reset_proc_window ( );


protected:
    void update_console ( QString msg );
    QString get_time    ( );

private:
    Ui::ac3 *ui;
    QString csl_msg = ""; // console message
};
#endif // AC3_H
