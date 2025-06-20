/*
#ifndef SONAR_H
#define SONAR_H

#include "QtOpenGLWidgets/qopenglwidget.h"
#include <QMainWindow>
#include <QWidget>
#include <QWindow>

#include <QOpenGLFunctions>
#include <QPaintDevice>
#include <QTimer>

namespace Ui
{
    class sonar;
}

class sonar : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    public:
        explicit sonar(QWidget *parent = nullptr);
        ~sonar();

    signals:
        void sonar_closed();

    protected:
        bool event(QEvent *event);
        void initialize( );
        void paintGL( );
        void closedEvent(QCloseEvent *event);

    private:
        Ui::sonar *ui;

};

#endif // SONAR_H
*/
