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

    // 检查兴趣个数，处理三态复选框（代表：没有选、部分选、全选）
    void CheckHobbies();

private slots:
    void on_checkBox_Read_toggled(bool checked);

    void on_checkBox_Daze_toggled(bool checked);

    void on_checkBox_Climb_toggled(bool checked);

    void on_checkBox_Swim_toggled(bool checked);

    void on_checkBox_Shop_toggled(bool checked);

    void on_checkBox_Game_toggled(bool checked);

    void on_pushButton_Show_clicked();

    void on_commandLinkButton_Folder_clicked();

    void on_commandLinkButton_Web_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
