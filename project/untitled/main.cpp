#include "window.h"
#include "qkeytools.h"

int main(int argc, char *argv[]) {
    // TO DEBUG
    QApplication a(argc, argv);
    Window w;
    w.showFullScreen();

    QkeyTools::getInstance()->setMainWindowObject(&w);
    QkeyTools::getInstance()->setWidth(400);
    QkeyTools::getInstance()->setHeight(200);
    QkeyTools::getInstance()->Init(QkeyTools::BOTTOM, QkeyTools::BLACK, 10, 10);
    return a.exec();
}
