#include "controller/controller.h"
#include "model/nt17model.h"
#include "ui/nt17ui.h"
#include "command/nt17command.h"
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include "controller/nt17controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<QSerialPort> serialPort = std::make_shared<QSerialPort>();
    std::vector<std::shared_ptr<ExecCmd>> cmds;

    //создание и настройка UI
    int id = 10;
    std::shared_ptr<NT17Model> nt17Model = std::make_shared<NT17Model>();
    std::shared_ptr<NT17UI> nt17ui = std::make_shared<NT17UI>();
    std::shared_ptr<NT17Controller> uint17Controller = std::make_shared<NT17Controller>(id, nt17Model);
    NT17Controller::Props props = NT17Controller::Props({serialPort});
    uint17Controller->setProps(props);
    nt17ui->setController(uint17Controller);
    nt17ui->setModel(id, nt17Model);

    //модель для nt17ui
    nt17Model->setUpdateFunc([nt17ui](int id) {
        Q_UNUSED(id)

        nt17ui->update();
    });

    //Нажал
    emit nt17ui->run();
    emit nt17ui->stop();

    return a.exec();
}
