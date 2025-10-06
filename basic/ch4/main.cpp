#include "widget.h"
#include <QApplication>

#include "showmsg.h"
#include "recvvoid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    // 关联自定义的信号和槽
    ShowMsg s;
    QObject::connect(&w, SIGNAL(SendMsg(QString)), &s, SLOT(RecvMsg(QString)));
    // 有一点细节，就是 SendMsg 这些定义在类里面的，这里调用可以不加作用域吗？好像是的

    //关联 “被信号关联的信号” 和槽
    RecvVoid r;
    QObject::connect(&w, SIGNAL(send_void()), &r, SLOT(recv_void()));

    w.show();

    return a.exec();
}
