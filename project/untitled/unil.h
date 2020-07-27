#ifndef UNIL_H
#define UNIL_H
#include <QString>

#define PAGE_SIZE 200          //单页字数
#define BOOK_NUM  20           //
#define __LINUX__              //Linux
// 下面是主要属性结构体
struct basic_option {
    QString working_space = "/home/pi/Desktop/build-Textreader-unknown-Release/untitled/data/";
    QString template_data = "/home/pi/Desktop/build-Textreader-unknown-Release/untitled/template data/";
};

// 下面是主题读取的结构体
struct window_template {
    QString button_poweroff ,button_swichpage ,button_jump ,button_choose ,input_box_jump ,reader ,Text_area;
};
// 下面是文件换页结构体
struct textfile_swich_page {
    char str[255];             // 文件目录
    int  max_page ,page_number;// 页数，上次读到的页码
    bool IsFirstTime;
    int book[20];
    inline void init(QString name, qint64 file_size){
        memset(str,0x00,sizeof(str));
        QByteArray buf = name.toLatin1();
        char *b2 = buf.data();
        memcpy(this->str ,b2 ,buf.size());
        b2 = nullptr;
        max_page = file_size / PAGE_SIZE;
        if((file_size % PAGE_SIZE) != 0) {
            max_page+=1;
        }
    }
};

#endif // UNIL_H
