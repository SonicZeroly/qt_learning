#ifndef SHOWCHANGES_H
#define SHOWCHANGES_H

#include <QObject>

class ShowChanges : public QObject
{
    Q_OBJECT
public:
    explicit ShowChanges(QObject *parent = nullptr);
    ~ShowChanges();

signals:

public slots:
    void RecvValue(double v);   // 接收属性value
};

#endif // SHOWCHANGES_H
