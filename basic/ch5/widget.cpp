#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),    // QWidget构造函数里面会实现父子对象绑定
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 创建性别按钮虚拟分组
    m_pGenderGroup = new QButtonGroup(this);    // 类的动态分配需要传入构造参数
    m_pGenderGroup->addButton(ui->radioButtonMan, 0);   //设置id
    m_pGenderGroup->addButton(ui->radioButtonWoman, 1);

    // 创建状态按钮虚拟分组
    m_pStatusGroup = new QButtonGroup(this);
    m_pStatusGroup->addButton(ui->radioButtonBang, 0);
    m_pStatusGroup->addButton(ui->radioButtonMeng, 1);

    // 分组实现后，两个组的单选按钮就不会互斥

    connect(m_pGenderGroup, SIGNAL(buttonClicked(int)), this, SLOT(RecvGenderID(int)));
    connect(m_pStatusGroup, SIGNAL(buttonClicked(int)), this, SLOT(RecvStatusID(int)));

    // 初始化选中状态 （可选）
    ui->radioButtonMan->setChecked(true);
    ui->radioButtonBang->setChecked(true);
    ui->radioButton_0to19->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::RecvGenderID(int id){
    switch(id){
    case 0:
        qDebug()<<tr("性别：男");   // 好像还真是，英文可以不用tr，但是像中文这种容易发生编码错误的必须要tr
        break;
    case 1:
        qDebug()<<tr("性别：女");
    default:
        break;
    }
}

void Widget::RecvStatusID(int id){
    switch(id){
    case 0:
        qDebug()<<tr("状态：棒棒哒");
        break;
    case 1:
        qDebug()<<tr("状态：萌萌哒");
    default:
        break;
    }
}

// 下面的槽函数都是直接通过".ui->对应控件->右键->转到槽"自动生成的。这样实现自动关联，无需手动写connect函数
// QGroupBox 控件里的四个单选按钮没有设置虚拟组，所以需要通过各自的槽函数来处理

void Widget::on_radioButton_0to19_toggled(bool checked)
{
    if(checked){
        qDebug()<<tr("年龄段：0~19");
    }
    else{
        qDebug()<<tr("年龄段：不是0~19");
    }
}

void Widget::on_radioButton_20to39_toggled(bool checked)
{
    if(checked){
        qDebug()<<tr("年龄段：20~39");
    }
    else{
        qDebug()<<tr("年龄段：不是20~39");
    }
}

void Widget::on_radioButton_40to59_toggled(bool checked)
{
    if(checked){
        qDebug()<<tr("年龄段：40~59");
    }
    else{
        qDebug()<<tr("年龄段：不是40~59");
    }
}

void Widget::on_radioButton_above60_toggled(bool checked)
{
    if(checked){
        qDebug()<<tr("年龄段：60以上");
    }
    else{
        qDebug()<<tr("年龄段：60及以下");
    }
}

void Widget::on_pushButton_Show_clicked()
{
    QString strRes;
    int nGenderID = m_pGenderGroup->checkedId();    // checkedId
    switch(nGenderID){
    case 0:
        strRes += tr("性别：男\r\n");
        break;
    case 1:
        strRes += tr("性别：女\r\n");
        break;
    default:
        strRes += tr("性别：未选中\r\n");
        break;
    }

    int nStatusID = m_pStatusGroup->checkedId();
    switch(nStatusID){
    case 0:
        strRes += tr("状态：棒棒哒\r\n");
        break;
    case 1:
        strRes += tr("状态：萌萌哒\r\n");
        break;
    default:
        break;
    }

    // 使用 GroupBox 似乎没有ID一说，因此只能一个个判断
    if(ui->radioButton_0to19->isChecked()){     // isChecked
        strRes += tr("年龄段：0~19\r\n");
    }
    else if(ui->radioButton_20to39->isChecked()){
        strRes += tr("年龄段：20~39\r\n");
    }
    else if(ui->radioButton_40to59->isChecked()){
        strRes += tr("年龄段：40~59\r\n");
    }
    else if(ui->radioButton_above60->isChecked()){
        strRes += tr("年龄段：60以上\r\n");
    }

    QMessageBox::information(this, "Show", strRes);
}
