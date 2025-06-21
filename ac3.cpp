#include "ac3.h"
#include "ui_ac3.h"

ac3::ac3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ac3)
{
    ui->setupUi(this);

    connect(ui->sliderA, &QSlider::sliderMoved, this, &ac3::attach_process);
    connect(this, &ac3::send_console, this, &ac3::update_console );

    update_console(get_time( ) + "  " + "AC trainer by six © ");

    ph = new process_handler( parent );
    connect(ph, &process_handler::send_console, this, &ac3::send_console);
}

ac3::~ac3()
{
    delete ui;
}

void ac3::attach_process( )
{
    // assert if proc window is open
    if (this->property("is_proc_window") == true)
    {
        return;
    }

    // assert slider value
    if (ui->sliderA->value() == 1)
    {
        this->setProperty("is_proc_window", false);
        return;
    }

    // update console
    update_console("attaching to process...");

    // initialize process handler
    //process_handler *_ph = new process_handler( );
    ph->show( );

    // is_proc_window to true
    this->setProperty("is_proc_window", true);

    // connect signal close window
    connect(ph, &process_handler::ph_closed, this, &ac3::reset_proc_window);


}

void ac3::reset_proc_window( )
{
    this->setProperty("is_proc_window", false);
    ui->sliderA->setSliderPosition(0);

}

void ac3::update_console( QString msg )
{
    QString csl_msg = get_time( ) + " " + msg + "\n";

    QListWidgetItem *_lW = new QListWidgetItem(csl_msg, ui->listWidget );
    // QListWidgetItem *_lW = ui->listWidget->currentItem();
    QSize sz = _lW->sizeHint();
    QSize nz(sz.width(), sz.height());
    _lW->setSizeHint(nz);
    ui->listWidget->addItem(_lW);
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
