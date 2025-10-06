#include "inc/hello_widget.h"

// 构造函数定义
HelloWidget:: HelloWidget(QWidget *parent)  //传入父对象，根据父对象的特性初始化自己父类的变量；如果没有传入，则为独立窗口
                        :QWidget(parent){   //初始化列表，传入的parent再传入QWidget构造函数进行初始化（毕竟自己也有继承了父类的变量）
    resize(300, 200);
    m_labelInfo = new QLabel( tr("<h1>Hello Widget!</h1>"), this);  // 父对象为该窗口
    m_labelInfo->setGeometry(10, 10, 200, 40);  // 设置 QLabel 显示的矩形区域
}

// 析构函数定义
HelloWidget:: ~HelloWidget(){
    delete m_labelInfo;
    m_labelInfo = nullptr;
}
