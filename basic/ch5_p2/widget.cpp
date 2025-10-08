#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QCryptographicHash>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置密码框的显示模式
    // determines how the text entered in the line edit is displayed (or echoed) to the user

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonLogin_clicked()
{
    if(ui->lineEditUser->text().isEmpty()
            || ui->lineEditPassword->text().isEmpty()){
        // 此处使用 warning
        QMessageBox::warning(this, tr("警告信息"),tr("用户名或密码为空，无法登录"));
        return ;
    }

    m_strUser = ui->lineEditUser->text();
    m_passwordHash = QCryptographicHash::hash(ui->lineEditPassword->text().toUtf8(),QCryptographicHash::Sha3_256);

    QString strMsg = tr("用户名：")+m_strUser+tr("\r\n")+tr("密码 Hash：");
    strMsg += m_passwordHash.toHex();   // 密码Hash十六进制显示

    QMessageBox::information(this, tr("用户信息"),strMsg);
}

void Widget::on_pushButtonExit_clicked()
{
    this->close();
}
