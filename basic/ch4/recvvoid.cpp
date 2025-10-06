#include "recvvoid.h"
#include <QMessageBox>

RecvVoid::RecvVoid(QObject *parent) : QObject(parent)
{

}

RecvVoid::~RecvVoid(){

}

void RecvVoid::recv_void(){
    QMessageBox::information(NULL, tr("Show"), tr("Just a void"));
}
