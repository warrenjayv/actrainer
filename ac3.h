#ifndef AC3_H
#define AC3_H

#include <QMainWindow>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui {
class ac3;
}
QT_END_NAMESPACE

class ac3 : public QMainWindow
{
    Q_OBJECT

public:
    ac3(QWidget *parent = nullptr);
    ~ac3();

public slots:
    void attach_process ( );

protected:
    void update_console ( QString msg );
    QString get_time    ( );

private:
    Ui::ac3 *ui;
    QString csl_msg = ""; // console message
};
#endif // AC3_H
