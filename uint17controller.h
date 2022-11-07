#ifndef UINT17CONTROLLER_H
#define UINT17CONTROLLER_H

#include "controller.h"
#include "nt17model.h"
#include <QObject>
#include <QSerialPort>

class UINT17Controller : public QObject, public Controller
{
    Q_OBJECT
public:
    explicit UINT17Controller(int id, std::shared_ptr<NT17Model> model, QObject *parent = nullptr);

public slots:
    void start();
    void stop();

signals:

private:
    int m_id;
    std::shared_ptr<NT17Model> m_model;
};

#endif // UINT17CONTROLLER_H
