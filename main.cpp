#include "controller.h"
#include "nt17model.h"
#include "reppetercmd.h"
#include "responcehandler.h"
#include "uint17.h"
#include "command/nt17command.h"
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <uint17controller.h>

void reppeterCmd();

class DeviceNT17;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<QSerialPort> serialPort = std::make_shared<QSerialPort>();
    std::shared_ptr<ReppeterCmd> reppeterCmd = std::make_shared<ReppeterCmd>();//повторитель отправки комманд
    std::vector<std::shared_ptr<ExecCmd>> cmds;

    ResponceHandler respHandler;
    respHandler.setProps({serialPort, reppeterCmd, cmds});
    respHandler.setting();

    //создание и настройка UI
    int id = 10;
    std::shared_ptr<NT17Model> nt17Model = std::make_shared<NT17Model>();
    std::shared_ptr<UINT17> uint17 = std::make_shared<UINT17>();
    std::shared_ptr<UINT17Controller> uint17Controller = std::make_shared<UINT17Controller>(id, nt17Model);
    UINT17Controller::Props props = UINT17Controller::Props({serialPort, reppeterCmd, cmds});
    uint17Controller->setProps(props);
    uint17->setController(uint17Controller);
    uint17->setModel(id, nt17Model);

    //Можно создать модель для uint17
    nt17Model->setUpdateFunc([uint17](int id) {
        Q_UNUSED(id)

        uint17->update();
    });

    //Нажал
    emit uint17->run();
    emit uint17->stop();

    return a.exec();
}

void reppeterCmd() {
    ReppeterCmd reppeterCmd;
    int id = reppeterCmd.appendExecCmd([](){ qDebug() << "I'm working"; }, [](){ qDebug() << "delete cmd";});
    reppeterCmd.runExecCmd(id);
    QTimer::singleShot(0, [id, &reppeterCmd](){ reppeterCmd.removeExecCmd(id);});

    reppeterCmd.setReppet(10);
    for (int i = 0; i < 10; ++i) {
        int id = reppeterCmd.appendExecCmd([i](){ qDebug() << "I'm working i:" << i; }, [](){ qDebug() << "delete cmd";});
        reppeterCmd.runExecCmd(id);
    }
}

class DeviceNT17 {
public:
    int a = 5;
};
