#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget   //此处的Widget和上面UI作用域里的不是一个东西
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:       //槽函数声明标志（也可以跟private、protected）
    void FoodIsComing();    //槽函数
    void PrintText(const QString& text);

signals:    // 信号默认强制规定为公有类型
    void SendMsg(QString str);  // 自定义信号，只需要声明
    void send_void();

public slots:
    void button_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
