#include "controller.h"
#include "nt17model.h"
#include "uint17.h"
#include "command/nt17command.h"
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <uint17controller.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<QSerialPort> serialPort = std::make_shared<QSerialPort>();
    std::vector<std::shared_ptr<ExecCmd>> cmds;

    //создание и настройка UI
    int id = 10;
    std::shared_ptr<NT17Model> nt17Model = std::make_shared<NT17Model>();
    std::shared_ptr<UINT17> uint17 = std::make_shared<UINT17>();
    std::shared_ptr<UINT17Controller> uint17Controller = std::make_shared<UINT17Controller>(id, nt17Model);
    UINT17Controller::Props props = UINT17Controller::Props({serialPort});
    uint17Controller->setProps(props);
    uint17->setController(uint17Controller);
    uint17->setModel(id, nt17Model);

    //модель для uint17
    nt17Model->setUpdateFunc([uint17](int id) {
        Q_UNUSED(id)

        uint17->update();
    });

    //Нажал
    emit uint17->run();
    emit uint17->stop();

    return a.exec();
}
