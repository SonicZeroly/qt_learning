#include "widget.h"
#include "ui_widget.h"

#include <QRegExp>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QDebug>

// 数据验证器，规定输入内容的格式，以识别非法输入
// .ui 里通过给Label的名称前加上&，通过【伙伴关系编辑模式】设置伙伴快捷键编辑，使得可以通过快捷键进行单行编辑框的切换
// 也可以利用【伙伴关系编辑模式】设置单词补全，此处跳过

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置MAC输入模板
    ui->lineEdit_MAC->setInputMask("HH:HH:HH:HH:HH:HH");    // H表示不可忽略的占位字符，h则可以忽略

    // 定义IPv4正则表达式
    QRegExp re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
               "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    // 正则表达式验证器
    QRegExpValidator *reVali = new QRegExpValidator(re);
    ui->lineEdit_IP->setValidator(reVali);

    // 新建整数验证器
    QIntValidator *intVali = new QIntValidator(0, 65535);
    // 设置给lineEditPort
    ui->lineEdit_Port->setValidator(intVali);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_MAC_textChanged(const QString &arg1)
{
    qDebug()<<"MAC: "<<arg1;
}

void Widget::on_lineEdit_IP_textChanged(const QString &arg1)
{
    qDebug()<<"IP: "<<arg1;
}

void Widget::on_lineEdit_Port_textChanged(const QString &arg1)
{
    qDebug()<<"Port: "<<arg1;
}
