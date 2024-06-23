#ifndef AC3_H
#define AC3_H

#include <QMainWindow>

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

protected:
    void open_process( );

private:
    Ui::ac3 *ui;
};
#endif // AC3_H
