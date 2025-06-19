#ifndef SONAR_H
#define SONAR_H

#include <QMainWindow>
#include <QWidget>
#include <QWindow>

namespace Ui
{
    class sonar;
}

class sonar : public QWidget
{
    public:
        explicit sonar(QWidget *parent = nullptr);
        ~sonar();

    signals:
        void sonar_closed();

    protected:
        void closedEvent(QCloseEvent *event);

    private:
        Ui::sonar *ui;
};


#endif // SONAR_H
