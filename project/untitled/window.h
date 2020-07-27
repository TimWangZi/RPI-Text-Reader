#ifndef WINDOW_H
#define WINDOW_H
#include "unil.h"

#include <QFile>

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>
#include <QFileDialog>

#include <QApplication>

#ifdef __LINUX__
#include <sys/reboot.h>
#include <unistd.h>
#endif
/*
TODO:
*/
// For debug
#include <QDebug>
class Window : public QWidget {
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();
private:
    inline void init();                             // 初始化方法
    inline void read_template();                    // 主题读取方法
    inline void read_page_data();                   // 读取页面数据

    // 下面是各种回调函数
    inline void CallBack_button_swichpage_up();
    inline void CallBack_button_swichpage_down();
    inline void CallBack_button_jump();
    inline void CallBack_button_choose();
    inline void CallBack_button_poweroff();


    window_template stylestl;
    basic_option    option;

    QPushButton button_swichpage_up ,button_swichpage_down ,button_jump ,button_choose ,button_poweroff;
    QLineEdit   input_box_jump;
    QLabel      Text_area;
    QFile       file_device;                        // 文件设备 
    QString     context;                            // 显示文本

    textfile_swich_page Page_data;                  // 页面数据
};
#endif // WINDOW_H
