#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit_showback->setReadOnly(true);

}

Widget::~Widget()
{
    delete ui;
}

static uint8_t check_host_if_correct(QString host)
{
    char buf[10];
    /* Type C IP address, ez check here*/
    QStringList list = host.split(".");
    snprintf(buf, sizeof(buf), "%d", list.count());
    QMessageLogger().debug((qPrintable(buf)));
    if(list.count()!=4)return CHECK_FAILED;

    foreach (QString byte, list) {
        snprintf(buf, sizeof(buf), "%d", byte.toInt());
        QMessageLogger().debug((qPrintable(buf)));
        if(byte.toInt() > 0xff)return CHECK_FAILED;
    }

    return CHECK_OK;
}

static uint8_t check_username_if_correct(QString username)
{
    return CHECK_OK;
}

static uint8_t check_password_if_correct(QString username)
{
    return CHECK_OK;
}

static uint8_t check_port_if_correct(QString port)
{
    return CHECK_OK;
}

uint8_t Widget::terminal_show_info(QString info, uint8_t debug_level)
{
    QColor textcolor_black,textcolor_red,textcolor_green,textcolor_blue,textcolor_yellow;

    textcolor_black.setRgb(0, 0, 0, 255);
    textcolor_red.setRgb(255, 0, 0, 255);
    textcolor_green.setRgb(0, 255, 0, 255);
    textcolor_blue.setRgb(0, 0, 255, 255);
    textcolor_yellow.setRgb(255, 220, 0, 255);

    switch(debug_level){
    default:
        break;
    case LEVEL_NORMAL:
        Widget::ui->textEdit_showback->setTextColor(textcolor_black);
        break;
    case LEVEL_OK:
        Widget::ui->textEdit_showback->setTextColor(textcolor_green);
        break;
    case LEVEL_WARNING:
        Widget::ui->textEdit_showback->setTextColor(textcolor_yellow);
        break;
    case LEVEL_ERROR:
        Widget::ui->textEdit_showback->setTextColor(textcolor_red);
        break;
    }
    Widget::ui->textEdit_showback->insertPlainText(info);
    Widget::ui->textEdit_showback->setTextColor(textcolor_black);

    return CHECK_OK;
}

//uint8_t Widget::save_user_to_local(User user)
//{

//}

static uint8_t do_connect(User user)
{

}

void Widget::on_Button_connect_clicked()
{
    User user_in;
//    user_in = (User *)malloc(sizeof(User));

    user_in.host =  ui->lineEdit_host->text();
    user_in.username  = ui->lineEdit_username->text();
    user_in.password  = ui->lineEdit_password->text();
    user_in.port  = ui->lineEdit_port->text();

    if((check_host_if_correct(user_in.host)         && \
       check_username_if_correct(user_in.username)  && \
       check_password_if_correct(user_in.password)  && \
       check_port_if_correct(user_in.port)))
    {
        QMessageLogger().debug((qPrintable("All things checked okay.")));
        Widget::terminal_show_info("Connecting...", LEVEL_NORMAL);


        /* if remerber me has checked, save this user to local,
         * and auto fill the last user in line edit when program next run */
        if(ui->checkBox_remerber_me->isChecked()){
            QMessageLogger().debug((qPrintable("Please remerber me.")));
        }

        /* should create a thread and connect to the host ,
         *  then handler the operations from main widget.
         * Finally do connect*/
        do_connect(user_in);
    }
    else
    {
        QString info_check_failed = "Connection failed....\n";
        Widget::terminal_show_info(info_check_failed, LEVEL_ERROR);
//        Widget::terminal_show_info(info_check_failed, LEVEL_OK);
//        Widget::terminal_show_info(info_check_failed, LEVEL_NORMAL);
//        Widget::terminal_show_info(info_check_failed, LEVEL_WARNING);

    }



}
