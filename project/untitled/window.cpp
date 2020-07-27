 #include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent) {
    read_page_data();
    read_template();
    init();
}
inline void Window::init() {
    // 恢复上一次的数据
    QString post(Page_data.str);
    if(post.length()<2)
        context = "你还没有阅读过任何的内容";
    else {
        file_device.setFileName(QString(Page_data.str));
        if(!file_device.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::critical(NULL, "文件跑路了(查无此文件)" , "你上次阅读的"+QString(Page_data.str)+"带着他的小姨子跑了" ,QMessageBox::Cancel | QMessageBox::Default ,0 ,0);
        }else{
            QTextStream text_stream(&file_device);
            text_stream.setCodec(QTextCodec::codecForName("utf-8"));
            text_stream.seek(Page_data.page_number * PAGE_SIZE);
            context = text_stream.read(PAGE_SIZE);
            for(int i=0;i<3;i++){
                if(context[0]==65533&&i<context.length()){
                    context.remove(0,1);
                }
            }
        }
    }

    // 下面为页面初始化

    // 换页按钮初始化
    button_swichpage_up.setParent(this);
    button_swichpage_up.move(0, 0);
    button_swichpage_up.resize(50, 20);
    button_swichpage_up.setText("下一页");
    button_swichpage_up.setStyleSheet(stylestl.button_swichpage);
    button_swichpage_up.show();

    // 换页按钮初始化2
    button_swichpage_down.setParent(this);
    button_swichpage_down.move(52, 0);
    button_swichpage_down.resize(50, 20);
    button_swichpage_down.setText("上一页");
    button_swichpage_down.setStyleSheet(stylestl.button_swichpage);
    button_swichpage_down.show();

    // 跳转按钮初始化
    button_jump.setParent(this);
    button_jump.move(200, 0);
    button_jump.resize(50, 20);
    button_jump.setText("跳转");
    button_jump.setStyleSheet(stylestl.button_jump);
    button_jump.show();

    // 文件选择按钮初始化
    button_choose.setParent(this);
    button_choose.move(260, 0);
    button_choose.resize(50, 20);
    button_choose.setText("选择");
    button_choose.setStyleSheet(stylestl.button_choose);
    button_choose.show();

    // 关机按钮初始化
    button_poweroff.setParent(this);
    button_poweroff.move(370, 0);
    button_poweroff.resize(50, 20);
    button_poweroff.setText("关机");
    button_poweroff.setStyleSheet(stylestl.button_choose);
    button_poweroff.show();

    // 跳转框初始化
    input_box_jump.setParent(this);
    input_box_jump.move(110, 0);
    input_box_jump.resize(90, 20);
    input_box_jump.setStyleSheet(stylestl.input_box_jump);
    input_box_jump.show();

    // 阅读区初始化
    Text_area.setParent(this);
    Text_area.move(0, 20);
    Text_area.resize(420, 300);
    Text_area.setWordWrap(true);
    Text_area.setStyleSheet(stylestl.Text_area);
    Text_area.show();
    Text_area.setText(context);

    // 背景初始化
    this->setStyleSheet(stylestl.reader);

    // 下面为信号绑定
    connect(&button_swichpage_up, &QPushButton::released, this, &Window::CallBack_button_swichpage_up);
    connect(&button_swichpage_down, &QPushButton::released, this, &Window::CallBack_button_swichpage_down);
    connect(&button_choose, &QPushButton::released, this, &Window::CallBack_button_choose);
    connect(&button_jump, &QPushButton::released, this, &Window::CallBack_button_jump);
    connect(&button_poweroff, &QPushButton::released, this, &Window::CallBack_button_poweroff);
    // END OF INIT
}

inline void Window::read_template(){

    // 主题文本读取（水代码）
    QFile tmf(option.template_data + "button_swichpage");
    if ( !tmf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(NULL, "主题文件读取失败" , "主题文件'button_swichpage'无法找到或读取失败，将尝试使用默认主题" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
    }
    QTextStream txtInput1(&tmf);
    stylestl.button_swichpage = txtInput1.readAll();
    tmf.close();

    tmf.setFileName(option.template_data + "button_jump");
    if ( !tmf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(NULL, "主题文件读取失败" , "主题文件'button_jump'无法找到或读取失败，将尝试使用默认主题" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
    }
    QTextStream txtInput3(&tmf);
    stylestl.button_jump = txtInput3.readAll();
    tmf.close();

    tmf.setFileName(option.template_data + "button_choose");
    if ( !tmf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(NULL, "主题文件读取失败" , "主题文件'button_choose'无法找到或读取失败，将尝试使用默认主题" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
    }
    QTextStream txtInput4(&tmf);
    stylestl.button_choose = txtInput4.readAll();
    tmf.close();

    tmf.setFileName(option.template_data + "input_box_jump");
    if ( !tmf.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::critical(NULL, "主题文件读取失败" , "主题文件'input_box_jump'无法找到或读取失败，将尝试使用默认主题" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);

    QTextStream txtInput5(&tmf);
    stylestl.input_box_jump = txtInput5.readAll();
    tmf.close();

    tmf.setFileName(option.template_data + "reader");
    if ( !tmf.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::critical(NULL, "主题文件读取失败" , "主题文件'reader'无法找到或读取失败，将尝试使用默认主题" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);

    QTextStream txtInput6(&tmf);
    stylestl.reader = txtInput6.readAll();
    tmf.close();

    tmf.setFileName(option.template_data + "Text_area");
    if ( !tmf.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::critical(NULL, "主题文件读取失败" , "主题文件'Text_area'无法找到或读取失败，将尝试使用默认主题" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);

    QTextStream txtInput7(&tmf);
    stylestl.Text_area = txtInput6.readAll();
    tmf.close();
}

inline void Window::read_page_data(){
    QFile read_data(option.working_space + "option.dat");
    if ( !read_data.open(QIODevice::ReadOnly)){
        QMessageBox::critical(NULL, "设置文件丢失" , "设置文件丢失,我们将重新创建新的设置文件,阅读进度将丢失。" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
        read_data.open(QIODevice::WriteOnly);
        context = "你还没有阅读过任何的内容";
    }else {
        read_data.read((char*)&Page_data ,sizeof (Page_data));
    }
    read_data.close();
}


// 下面为函数回调
inline void Window::CallBack_button_jump() {
    // 跳转显示
    if(input_box_jump.text().length() == 0 || /*在此处填入文件未读入判断*/file_device.handle() == -1){
        QMessageBox::warning(NULL, "注意" , "输入框没有输入任何内容" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
    } else {
        if(input_box_jump.text().toInt()>=Page_data.max_page){
            QMessageBox::warning(NULL, "注意" , "超出最大页数:" + QString::number(Page_data.max_page) ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
            return;
        }
        QTextStream text_stream(&file_device);
        text_stream.setCodec(QTextCodec::codecForName("utf-8"));
        Page_data.page_number = input_box_jump.text().toInt();
        text_stream.seek(Page_data.page_number * PAGE_SIZE);
        context = text_stream.read(PAGE_SIZE);
        for(int i=0;i<3;i++){
            if(context[0]==65533&&i<context.length()){
                context.remove(0,1);
            }
        }
        qDebug() << context.length() << '\t' << Page_data.page_number * PAGE_SIZE;
        Text_area.setText(context);
    }
}

inline void Window::CallBack_button_choose() {
    // For unknown reason the QFileDialog can't be used in linux
#ifdef __LINUX__
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setModal(QFileDialog::ExistingFiles);
    fileDialog.setOption(QFileDialog::DontUseNativeDialog);
    fileDialog.exec();
    QByteArray buf1 = fileDialog.selectedFiles().at(0).toLatin1();
    char *b2 = buf1.data();
    char str[buf1.size()+1];
    memcpy(str ,b2 ,buf1.size());
    b2 = nullptr;
    str[buf1.size()]='\0';
    QString string1(str);
#else
    auto string1 = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));
#endif
    if(file_device.handle() != -1){
        file_device.close();
    }
    file_device.setFileName(string1);
    if(string1.length()==0){
        return;
    }
    if(!file_device.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(NULL, "无法打开文件" , "文本文件无法打开" ,QMessageBox::Cancel | QMessageBox::Default ,0 ,0);
        file_device.setFileName(QString(Page_data.str));
        file_device.open(QIODevice::ReadOnly | QIODevice::Text);
    } else {
        Page_data.page_number = 0;
        QByteArray buf = string1.toLatin1();
        Page_data.init(string1 ,file_device.size());
        QTextStream text_stream(&file_device);
        text_stream.setCodec(QTextCodec::codecForName("utf-8"));
        text_stream.seek(0);
        context = text_stream.read(PAGE_SIZE);
        for(int i=0;i<3;i++){
            if(context[0]==65533&&i<context.length()){
                context.remove(0,1);
            }
        }
        qDebug() << context.length() << '\t' << Page_data.page_number * PAGE_SIZE;
        Text_area.setText(context);
    }
}

inline void Window::CallBack_button_swichpage_up() {
    if(Page_data.page_number<Page_data.max_page){
        Page_data.page_number++;
        QTextStream text_stream(&file_device);
        text_stream.setCodec(QTextCodec::codecForName("utf-8"));
        text_stream.seek(Page_data.page_number * PAGE_SIZE);
        context = text_stream.read(PAGE_SIZE);
        for(int i=0;i<3;i++){
            if(context[0]==65533&&i<context.length()){
                context.remove(0,1);
            }
        }
        qDebug() << context.length() << '\t' << Page_data.page_number * PAGE_SIZE;
        Text_area.setText(context);
    } else {
        QMessageBox::warning(NULL, "。" , "已到末页" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
    }
}

inline void Window::CallBack_button_swichpage_down() {
    if(Page_data.page_number > 0){
        Page_data.page_number--;
        QTextStream text_stream(&file_device);
        text_stream.setCodec(QTextCodec::codecForName("utf-8"));
        text_stream.seek(Page_data.page_number * PAGE_SIZE);
        context = text_stream.read(PAGE_SIZE);
        for(int i=0;i<3;i++){
            if(context[0]==65533&&i<context.length()){
                context.remove(0,1);
            }
        }
        qDebug() << context.length() << '\t' << Page_data.page_number * PAGE_SIZE;
        Text_area.setText(context);
    } else {
        QMessageBox::warning(NULL, "Are You Silly B?" , "这就是第一页啊" ,QMessageBox::Cancel|QMessageBox::Default ,0 ,0);
    }
}

inline void Window::CallBack_button_poweroff() {
    QFile file;
    file.setFileName(option.working_space + "option.dat");
    file.open(QIODevice::WriteOnly);
    file.write((char*)(&Page_data) ,sizeof(Page_data));
    file.close();
#ifdef __LINUX__
    /*sync();
    reboot(RB_POWER_OFF);*/
    system("sudo shutdown -P now");
#else
    system("shutdown /s /t 0");
#endif
    // system("sudo halt");
    QApplication::quit();
}

Window::~Window() {
    file_device.close();
}
