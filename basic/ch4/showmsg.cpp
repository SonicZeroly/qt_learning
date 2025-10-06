#include "showmsg.h"
#include <QMessageBox>

ShowMsg::ShowMsg(QObject *parent) : QObject(parent)
{

}

ShowMsg::~ShowMsg(){

}

/**
 * @brief [槽函数]接收自定义信号
 */
void ShowMsg::RecvMsg(QString str){
    QMessageBox::information(NULL, tr("Show"), str);
}
