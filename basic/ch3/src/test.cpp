#include "inc/test.h"
#include <QObject>
#include <QDebug>
/**
 * @brief setNum 函数示例（转入函数：将数值变量转为字符串）
 * @details 用于将数值类型转换为QString
 */
void test_setnum(){
    QString strTest;

    short numHex = 127;
    strTest.setNum(numHex, 16); // 第二个参数（base）表示进制格式，16表示转换为十六进制字符串
    qDebug()<<"Hex: " <<strTest;

    float numFixed = 123.78999;
    strTest.setNum(numFixed, 'f', 3);   //第二个参数表示目标字符串格式，第三个参数指定浮点数精度
    qDebug()<<"Fixed: "<<strTest;
}


/**
 * @brief arg 转换函数示例（转入函数）
 * @details arg 函数比 setNum 函数功能更强大，可以设置目标字符串宽度和填充字符。
 */
void test_arg(){
    QString strRes{};

    long num1 = 800;
    QString strMod = QObject::tr("Normal: %1");     //%1是占位符，类似于%d
    strRes = strMod.arg(num1);
    qDebug()<<"Mod: "<<strMod<<" \t Result: "<<strRes;

    int num2 = 63;

    // [arg参数]：fieldWidth 目标字符串宽度；base 进制；fillChar 填充字符，用于补充多出来的宽度（编译一次懂什么意思了）
    strRes = QObject::tr("Qct: %1").arg(num2, 4, 8, QChar('0'));
    qDebug()<<strRes;

    // arg串联使用
    short num3 = 127;
    QString strPrefix = QObject::tr("0x");
    strRes = QObject::tr("Hex: %1%2").arg(strPrefix).arg(num3, 0, 16);  //宽度给0表示自动识别
    qDebug() << strRes;

    double num4 = 123.78999;
    strRes = QObject::tr("Fixed: %1 \t Scientific: %2").arg(num4, 0, 'f').arg(num4, 0, 'e', 3);
    qDebug()<<strRes;

    //占位符可在字符串中重复使用
}


/**
 * @brief toXXX转出函数示例（转出函数：将字符串转为数值变量）
 * @details 转入函数重载了不同类型，但是转出函数则不行，因而有对应不同函数名
 */
void test_tovalue(){
    bool bok = false;

    QString str1 = QObject::tr("800");
    int nDec = str1.toInt(&bok, 10);
    qDebug() << nDec << "\t" << bok;
//    qDebug() << QObject::tr("Result is ") << nDec << QObject::tr(", Transform ") << bok;

    QString str2 = QObject::tr("FFFF");
    nDec = str2.toInt(&bok, 10);    //类型不匹配，错误
    qDebug() << nDec << "\t" << bok;
    short nHexShort = str2.toShort(&bok, 16);  //数据类型范围不足
    qDebug() << nHexShort << "\t" << bok;
    ushort nHexUShort = str2.toUShort(&bok, 16);  //正确
    qDebug() << nHexUShort << "\t" << bok;

    // 进制的自动转换
    QString str3 = QObject::tr("0077");
    int nOct = str3.toInt(&bok, 0);     //输入0，自动转换为八进制
    qDebug() << nOct << "\t" << bok;

    // 浮点数转换
    QString str4 = QObject::tr("123.78999");
    double nFixed = str4.toDouble(&bok);
    qDebug() << nFixed << "\t" << bok;
    // 科学计数法
    QString str5 = QObject::tr("1.238e-5");
    double dblScientific = str5.toDouble(&bok);
    qDebug() << dblScientific << "\t" << bok;
}

/**
 * @brief 字符串运算符使用
 */
/**
 * 内容好像比较机械，跳过了。记录以下其中存在的浅拷贝、深拷贝知识：
 *
 * 赋值运算符 = 的隐式共享（Implicit Sharing），在执行赋值时，真正的字符串数据拷贝没有发生，这是为了优化运行效率，避免大量数据的拷贝。
 * 隐式共享实现方式就是对数据块做引用计数，多一个对象赋值或 参数、返回值拷贝时，引用次数加 1，
 * 这个赋值过程只需要设置一下数据指针和增加引用计数，不会真的拷贝大量数据，这种拷贝称为浅拷贝（shallow copy）。
 *
 * 在赋值的一个字符串发生变化，要做写入修改时，这个要发生变化的字符串会重新分配一块内存，将旧的数据拷贝到新的内存空间，并对其做相应的写入修改，
 * 这个过程叫深 拷贝（deep copy），也可称为 copy-on-write（写时拷贝）。深拷贝会将旧的数据块引用计数减 1，然后将变化的字符串数据指向新空间，新空间引用计数加 1。
 */

/**
 * @brief 子串处理函数示例
 */
void test_substring(){
    QString strOne = "abcd";
    QString strThree = strOne.repeated(3);

    qDebug() << strThree.isEmpty();   // 判断是否为空
    qDebug() << strThree.length() << "\t" << strThree.size();   // 输出长度
    qDebug() << strThree;

    // 字串查询
    qDebug() << strThree.contains(strOne);
    qDebug() << strThree.count(strOne);
    qDebug() << strThree.startsWith(strOne);
    qDebug() << strThree.indexOf(strOne);
    qDebug() << strThree.lastIndexOf(strOne);

    // 剔除两端空白
    QString str_ComplexName = QObject::tr("    /home/user/a.txt  \t\t ");
    QString str_FileName = str_ComplexName.trimmed();
    qDebug() << str_FileName;

    if(str_FileName.endsWith(QObject::tr(".txt"))){
        qDebug() << "Here is a .txt file";
    }

    // 分隔子串
    QStringList substr_list = str_FileName.split(QChar('/'));
    for(int i=0; i<substr_list.length(); i++){
        qDebug() << i << "\t" << substr_list[i];
     }
    // 获取段落
    QString subs_section = str_FileName.section(QChar('/'), 2, 3);
    qDebug() << subs_section;
}

/**
 * @brief 输入输出流示例
 */

// 暂时跳过



