#include "ac3.h"
#include "ui_ac3.h"

ac3::ac3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ac3)
{
    ui->setupUi(this);
    connect(ui->sliderA, &QSlider::sliderMoved, this, &ac3::attach_process);

    update_console(get_time( ) + " AC trainer by SIX © ");

}

ac3::~ac3()
{
    delete ui;
}

void ac3::attach_process( )
{

}

void ac3::update_console( QString msg )
{
    csl_msg += msg + "\n";

    ui->console_LBL->setText(csl_msg);
}

QString ac3::get_time ( )
{
    auto now = std::chrono::system_clock::now( );
    std::time_t cut = std::chrono::system_clock::to_time_t(now);
    return QString::fromStdString(std::ctime(&cut));
}
