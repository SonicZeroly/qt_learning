#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>  // 头文件里声明了用于弹消息框的类
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 将信号和槽关联起来（connect 函数必须放在 ui->setupUi 之后，否则控件指针是未定义的野指针）
    // connect参数：发送对象指针, 发送的信号, 接收对象指针, 接收对象的槽函数
    // 也可以通过 Ui 设计界面配置自动关联，就无需手动敲connect
#if 1
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(FoodIsComing()));     // 旧语法
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(FoodIsComing()));

    connect(ui->lineEdit, SIGNAL(textEdited(QString)), ui->label, SLOT(setText(QString)));  // QString在这应该不是实例，而是类似函数宏定义那样
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(PrintText(QString)));

    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SIGNAL(send_void()));        //信号关联信号
#else
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::FoodIsComing);    // 新语法
#endif

    // 除了关联connect，还有取消关联disconnect，实际应用就好像那种一次性按钮，点完后就暗下来
    // 除了关联信号和槽，还能关联信号和信号（即一个信号触发另一个信号），不过信号与信号之间的声明格式（参数、返回类型）要相同

}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief [槽函数]送餐槽函数定义
 */
void Widget::FoodIsComing(){
    // 处理多信号：获取信号源头对象的名称
    QString strSenderName = this->sender()->objectName();   // 发送对象和接收对象进行了connect，能从接收端找出发送端也不奇怪
    QString strMsg;

    // swicth不支持字符串
    if("pushButton" == strSenderName)       strMsg = tr("我的外卖已送达");
    else if("pushButton_2" == strSenderName)       strMsg = tr("A的外卖已送达");
    else if("pushButton_3" == strSenderName)       strMsg = tr("Z的外卖已送达");

#if 0
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("送餐"));
    msgBox.setText(tr("外卖已送达"));
    msgBox.exec();  //模态显示
#else   // 消息框内容格式相对单调，是可以做成预定义的消息框供程序员直接调用
    QMessageBox::information(this, tr("送餐"), strMsg);  //因为在QObject相关子类中，所以直接用tr
#endif
}

/**
 * @brief [槽函数]定义打印文本到控制台
 */
void Widget::PrintText(const QString& text){
    qDebug() << text;
}

/**
 * @brief [槽函数]作为源端发送信号
 * @note  比较有意思的是，这里 button_clicked() 是槽，但是里面调用的是信号
 *        这里看似可以用“信号关联信号”，但是两信号的声明格式不同
 */
void Widget::button_clicked(){
    emit SendMsg(tr("This is a message"));   // SendMsg是信号，也就是放在SIGNAL()里面的，只有声明没有函数主体，传入的参数也是通过connect的写法传到槽函数
}


