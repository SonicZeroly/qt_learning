#include "widget.h"
#include <QApplication>
#include <qDebug>
#include "showchanges.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    ShowChanges s;

    QObject::connect(&w, SIGNAL(valueChanged(double)), &s, SLOT(RecvValue(double)));
    // 感觉这种可以说是“属性关联”（自己造的词），ch4那种算是“事件关联”

    w.setNickname("Nick");
    qDebug() << w.nickname();
    w.setCount(100);
    qDebug() << w.count();
    w.setProperty("value", 5.0);    //对于交给moc自动声明读写函数的，这样调用
    qDebug() << w.property("value").toDouble();    //property() 返回一个通用的 QVariant 对象，将 QVariant 对象转为标准类型或者 Qt 数值类型，可以用对应的 toXXX 函数


    /* 动态属性创建（无需在头文件的类里面进行属性声明） */
    qDebug()<<w.property("myvalue").isValid();

    // 创建动态属性
    w.setProperty("myvalue", 3.14);
    w.setProperty("myname", "zero");

    // 在使用方法上和上面的value很类似
    qDebug() << w.property("myvalue").toDouble();
    qDebug() << w.property("myname");

    // 获取所有动态属性名称
    qDebug() << w.dynamicPropertyNames();

    w.show();
    return a.exec();
}
