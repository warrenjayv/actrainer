#ifndef ERR_H
#define ERR_H

#include <QMainWindow>
#include <QWidget>
#include <QWindow>

namespace Ui
{
class errs;
}


class errs : public QWidget
{
    Q_OBJECT
public:
    explicit errs(QWidget *parent = nullptr);
    ~errs();
private:
    Ui::errs *ui;

};


#endif // ERR_H
