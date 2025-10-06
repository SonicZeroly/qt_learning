#ifndef RECVVOID_H
#define RECVVOID_H

#include <QObject>

class RecvVoid : public QObject
{
    Q_OBJECT
public:
    explicit RecvVoid(QObject *parent = nullptr);
    ~RecvVoid();

signals:

public slots:
    void recv_void();
};

#endif // RECVVOID_H
