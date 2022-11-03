#ifndef UINT17_H
#define UINT17_H

#include <QObject>

class UINT17 : public QObject
{
    Q_OBJECT
public:
    explicit UINT17(QObject *parent = nullptr);

signals:
    void run();
    void stop();
};

#endif // UINT17_H
