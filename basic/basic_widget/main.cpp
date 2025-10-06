#include "widget.h"
#include "inc/hello_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    HelloWidget hw; //不传入父对象，生成独立窗口
    hw.show();

    return a.exec();
}
