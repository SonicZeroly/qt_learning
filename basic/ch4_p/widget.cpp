#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

/* 读函数定义 */
const QString& Widget::nickname(){
    return m_nickname;
}

int Widget::count(){
    return m_count;
}

/* 写函数定义 */
void Widget::setNickname(const QString& strNewName){
    if(strNewName == m_nickname){
        return ;
    }
    m_nickname = strNewName;
    emit nicknameChanged(strNewName);       // 通知信号是在这里发出的
}

void Widget::setCount(int nNewCount){
    if(nNewCount == m_count){
        return ;
    }
    m_count = nNewCount;
    emit countChanged(nNewCount);
}

