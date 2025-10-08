#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

#include <QDesktopServices>
#include <QUrl>     // 描述外部链接

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->checkBox_Tristate->setTristate(true);   // 设置三态工作模式
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_checkBox_Read_toggled(bool checked)
{
    CheckHobbies();     // 更新三态复选框状态
}

void Widget::on_checkBox_Daze_toggled(bool checked)
{
    CheckHobbies();
}

void Widget::on_checkBox_Climb_toggled(bool checked)
{
    CheckHobbies();
}

void Widget::on_checkBox_Swim_toggled(bool checked)
{
    CheckHobbies();
}

void Widget::on_checkBox_Shop_toggled(bool checked)
{
    CheckHobbies();
}

void Widget::on_checkBox_Game_toggled(bool checked)
{
    CheckHobbies();
}

void Widget::on_pushButton_Show_clicked()
{
    QString strRes = tr("兴趣爱好是：\r\n");

    if(ui->checkBox_Climb->isChecked()){
        strRes += tr("爬山\r\n");
    }
    if(ui->checkBox_Daze->isChecked()){
        strRes += tr("发呆\r\n");
    }
    if(ui->checkBox_Game->isChecked()){
        strRes += tr("游戏\r\n");
    }
    if(ui->checkBox_Read->isChecked()){
        strRes += tr("阅读\r\n");
    }
    if(ui->checkBox_Shop->isChecked()){
        strRes += tr("逛街\r\n");
    }
    if(ui->checkBox_Swim->isChecked()){
        strRes += tr("游泳\r\n");
    }

    QMessageBox::information(this, "Show", strRes);
}

void Widget::on_commandLinkButton_Folder_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///J:/my_project/04_my_github/qt_learning/basic/ch5_p")); // 本地文件路径用 file:/// ,Url里统一使用/
}

void Widget::on_commandLinkButton_Web_clicked()
{
    QDesktopServices::openUrl(QUrl("https://qtguide.ustclug.org/"));
}

void Widget::CheckHobbies(){
    int count{};

    if(ui->checkBox_Climb->isChecked()){
        count++;
    }
    if(ui->checkBox_Daze->isChecked()){
        count++;
    }
    if(ui->checkBox_Game->isChecked()){
        count++;
    }
    if(ui->checkBox_Read->isChecked()){
        count++;
    }
    if(ui->checkBox_Shop->isChecked()){
        count++;
    }
    if(ui->checkBox_Swim->isChecked()){
        count++;
    }

    if(count == 0)      ui->checkBox_Tristate->setCheckState(Qt::Unchecked);
    else if(count < 6)  ui->checkBox_Tristate->setCheckState(Qt::PartiallyChecked);
    else if(count == 6)  ui->checkBox_Tristate->setCheckState(Qt::Checked);
}


