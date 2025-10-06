#ifndef HELLO_WIDGET_H
#define HELLO_WIDGET_H

#include <QWidget>
#include <QLabel>

class HelloWidget : public QWidget{
    Q_OBJECT    // 添加一些共用的内容
public:
    explicit HelloWidget(QWidget *parent = 0);  // explicit使构造函数不可用作转换构造函数
    ~HelloWidget();

    QLabel *m_labelInfo;
};

#endif // HELLO_WIDGET_H
