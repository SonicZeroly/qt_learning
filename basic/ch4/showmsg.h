#ifndef SHOWMSG_H
#define SHOWMSG_H

#include <QObject>

class ShowMsg : public QObject   // 要使用信号和槽机制，必须直接或间接从 QObject 类派生
{
    Q_OBJECT
public:
    explicit ShowMsg(QObject *parent = nullptr);
    ~ShowMsg();

signals:

public slots:
    void RecvMsg(QString str); // 槽函数声明的参数类型和返回类型要与 SendMsg 信号保持一致
};

#endif // SHOWMSG_H
