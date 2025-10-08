#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    // 属性声明（属性系统也是通过元对象系统实现的，需要直接或间接从 QObject 类继承，并在类的声明里需要 Q_OBJECT 宏）

    // 1.（属性类型）QString 属性名 READ 读函数 WRITE 写函数 NOTIFY 成员变量变化时的通知函数 （这种声明方法省略了成员变量）
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)

    // 2. 在其中声明成员变量
    Q_PROPERTY(int count MEMBER m_count READ count WRITE setCount NOTIFY countChanged)

    // 3. 声明成员变量，并省略读写函数，moc会自动生成
    Q_PROPERTY(double value MEMBER m_value NOTIFY valueChanged)

    /* 读函数声明 */
    const QString& nickname();
    int count();

signals:
    /* 属性数值变化时发送通知函数声明 */
    void nicknameChanged(const QString& strNewName);
    void countChanged(int nNewCount);
    void valueChanged(double dblNewValue);

public slots:
    /* 写函数声明 */
    void setNickname(const QString& strNewName);
    void setCount(int nNewCount);

private:
    Ui::Widget *ui;

    /* 属性成员变量声明 */
    QString m_nickname;
    int m_count;
    double m_value;
};

#endif // WIDGET_H
