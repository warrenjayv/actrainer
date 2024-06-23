#include "ac3.h"
#include "ui_ac3.h"

ac3::ac3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ac3)
{
    ui->setupUi(this);
}

ac3::~ac3()
{
    delete ui;
}

void ac3::open_process( )
{

}
