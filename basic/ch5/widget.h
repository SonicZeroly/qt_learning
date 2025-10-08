#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup> // 按钮分组头文件

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void RecvGenderID(int id);
    void RecvStatusID(int id);

private slots:  // "对应控件->右键->转到槽"自动生成的
    void on_radioButton_0to19_toggled(bool checked);

    void on_radioButton_20to39_toggled(bool checked);

    void on_radioButton_40to59_toggled(bool checked);

    void on_radioButton_above60_toggled(bool checked);

    void on_pushButton_Show_clicked();

private:
    Ui::Widget *ui;

    // 如果不分组，单选按钮之间会互斥
    QButtonGroup* m_pGenderGroup;
    QButtonGroup* m_pStatusGroup;
};

#endif // WIDGET_H
