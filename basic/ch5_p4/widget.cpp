#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QIntValidator>    // 包含整数验证器类，用于限定字号的范围。
#include <QFont>    // 包含综合字体格式类，用于感知或设置文本格式。
#include <QColorDialog>     // 包含颜色设置对话框，提供给用户选取文字前景色或者背景色。
#include <QBrush>   // 包含画刷类，在进行颜色感知时，需要通过前景色画刷和背景色画刷来感知。

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 二态按钮
    ui->pushButtonBold->setCheckable(true);
    ui->pushButtonItalic->setCheckable(true);
    ui->pushButtonUnderline->setCheckable(true);

    // 用整数检验器来保持字体大小输入合法
    QIntValidator* fontsize_vali = new QIntValidator(0, 72);    // 字号原本是浮点数，这里简化为整数
    ui->lineEditFontSIze->setValidator(fontsize_vali);

    // 字体家族设置，直接关联组合框信号与编辑框槽函数
    connect(ui->fontComboBox, SIGNAL(currentIndexChanged(QString)),
            ui->textEdit, SLOT(setFontFamily(QString)));

    // 编辑框初始内容
    ui->textEdit->setHtml("<b>粗体字的行<br></b>"
                          "<i>斜体字的行<br></i>"
                          "<u>下划线的行<br></u>"
                          "<font style=\"color:red;\">文本前景色<br></font>"
                          "<font style=\"background:yellow;\">文本背景色<br></font>"
                          "<font style=\"font-size:18pt;\">字号大小变化的行<br></font>"
                          "<font style=\"font-family:黑体;\">字体家族变化的行<br></font>");   // 里面的\是C++的转义字符
}

Widget::~Widget()
{
    delete ui;
}

// 下面这些设置函数会自动对丰富文本编辑控件里选中的文本生效，而不要通过 QTextEdit 内部的文档或光标来操作

void Widget::on_pushButtonBold_clicked(bool checked)
{
    if(checked){
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else{
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}

void Widget::on_pushButtonItalic_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
}

void Widget::on_pushButtonUnderline_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}

void Widget::on_pushButtonColor_clicked()
{
    // 这个静态函数自动弹出颜色对话框，提供给用户取色，然后返回一个 QColor 对象。
    // 如果用户选取了颜色（用户点击确定按钮），那么返回对象是可用的，否则返回的颜色对象处于不可用状态（用户点击取消按钮）。
    QColor clr = QColorDialog::getColor(Qt::black); // 默认黑色
    if(clr.isValid()){  // 可以用颜色对象的函数 isValid()  获知返回值的状态。
        ui->textEdit->setTextColor(clr);

        // 对“前景色”按钮同步该颜色设置
        QString strSS = tr("color: %1").arg(clr.name());
        ui->pushButtonColor->setStyleSheet(strSS);  // 设置按钮的QSS
    }
}

void Widget::on_pushButtonBGColor_clicked()
{
    // 弹出颜色选择，并设置背景颜色
    QColor clr = QColorDialog::getColor(Qt::white);
    if(clr.isValid()){
        ui->textEdit->setTextBackgroundColor(clr);
        QString strSS = tr("color: %1").arg(clr.name());
        ui->pushButtonBGColor->setStyleSheet(strSS);
    }
}

void Widget::on_lineEditFontSIze_editingFinished()
{
    // editingFinished() 信号会在单行编辑控件失去输入焦点，或者用户在单行编辑控件里按回车键时触发

    int nFontSize = ui->lineEditFontSIze->text().toInt();
    ui->textEdit->setFontPointSize(nFontSize);  // PointSize 即点阵大小的意思
}

// 前面函数修改了选中文字的格式，但是没有实时感知能力，这部分交给textEdit控件处理

// currentCharFormat 跟踪的是光标所在或选中的文字
void Widget::on_textEdit_currentCharFormatChanged(const QTextCharFormat &format)
{
    // 根据当前字体格式反过来设置按钮状态、样式
    if(format.fontWeight() == QFont::Bold){
        ui->pushButtonBold->setChecked(true);
    }
    else{
        ui->pushButtonBold->setChecked(false);
    }

    ui->pushButtonItalic->setChecked(format.fontItalic());
    ui->pushButtonUnderline->setChecked(format.fontUnderline());

    // 文本有可能是无格式的普通文本，对于这些无格式普通文本，前景色画刷和背景色画刷其实都是没有的

    QBrush brushText = format.foreground();
    if(brushText != Qt::NoBrush){   // 有前景画刷
        QColor clrText = brushText.color();
        QString strSS = tr("color: %1").arg(clrText.name());
        ui->pushButtonColor->setStyleSheet(strSS);
    }
    else{   // 无前景画刷
        ui->pushButtonColor->setStyleSheet("");
    }

    QBrush brushBG = format.background();
    if(brushBG != Qt::NoBrush){   // 有背景画刷
        QColor clrBG = brushBG.color();
        QString strSSBG = tr("color: %1").arg(clrBG.name());
        ui->pushButtonBGColor->setStyleSheet(strSSBG);
    }
    else{   // 无背景画刷
        ui->pushButtonBGColor->setStyleSheet("");
    }

    // 字体和字体家族检测一定要用 QFont 相关函数
    QFont curFont = format.font();

    int nFontSize = curFont.pointSize();
    if(-1 == nFontSize){    // 如果pt是-1，说明是px格式
        nFontSize = (int)(curFont.pixelSize() * 9.0/12.0);  // px换算为pt
    }
    ui->lineEditFontSIze->setText(QString("").setNum(nFontSize));

    QString strFontFamily = curFont.family();
    ui->fontComboBox->setCurrentText(strFontFamily);
}

// 当丰富文本编辑控件内容改变时调用
void Widget::on_textEdit_textChanged()
{
    qDebug()<<ui->textEdit->toHtml()<<endl;     // 打印丰富文本
}
