#include "mainwindow.h"
#include <QApplication>

#include "inc/test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    test_setnum();
//    test_arg();
//    test_tovalue();
    test_substring();

    return a.exec();
}
