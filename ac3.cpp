#include "ac3.h"
#include "ui_ac3.h"

ac3::ac3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ac3)
{
    ui->setupUi(this);
    connect(ui->sliderA, &QSlider::sliderMoved, this, &ac3::attach_process);

    update_console(get_time( ) + "   " + "AC trainer by SIX © ");

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
    int h = ( cut / 360 ) % 24;
    std::string hs = std::to_string(h);
    int m = ( cut / 60  ) % 60;
    std::string ms = std::to_string(m);
    int s = ( cut % 60  );
    std::string ss = std::to_string(s);

    return QString::fromStdString(hs + ":" + ms + ":" + ss);

    // return QString::fromStdString(std::ctime(&cut));
}
