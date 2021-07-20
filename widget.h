#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_Button_connect_clicked();

private:
    Ui::Widget *ui;
    uint8_t terminal_show_info(QString info, uint8_t debug_level);
};

#endif // WIDGET_H
