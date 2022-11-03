#include "reppetercmd.h"
#include "uint17.h"
#include "command/nt17command.h"
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QSerialPort>

void reppeterCmd();

class DeviceNT17;
struct ExecCmd {
    int id;
    std::shared_ptr<InterfaceCmd> cmd;
    std::shared_ptr<std::function<void ()>> succesFunc;
    std::shared_ptr<std::function<void (std::shared_ptr<InterfaceCmd> cmd)>> errorFunc;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //    reppeterCmd();
    std::shared_ptr<QSerialPort> serialPort = std::make_shared<QSerialPort>();
    std::shared_ptr<ReppeterCmd> reppeterCmd = std::make_shared<ReppeterCmd>();

    std::unique_ptr<UINT17> uint17 = std::make_unique<UINT17>();
    std::unique_ptr<DeviceNT17> devNT17 = std::make_unique<DeviceNT17>();
    std::vector<ExecCmd> cmds;
    QObject::connect(serialPort.get(), &QSerialPort::readyRead, [serialPort, &cmds]() {
        QByteArray byteRes = serialPort->readAll();
        auto it = std::find_if(cmds.begin(), cmds.end(), [byteRes](ExecCmd execCmd) {
            if (execCmd.cmd->isResAddress(byteRes) && execCmd.cmd->isResEquivalent(byteRes)) {
                return true;
            }
            return false;
        });
        if (it == cmds.end()) {
            return;
        }
        (*it->succesFunc.get())();
        cmds.erase(it);
    });
    //Настройка ui
    QObject::connect(uint17.get(), &UINT17::run, [serialPort, reppeterCmd, &cmds]() {
        std::shared_ptr<NT17Command> nt17Cmd = std::make_shared<NT17Command>();
        int id = reppeterCmd->appendExecCmd([nt17Cmd](){
            nt17Cmd;
        });
        reppeterCmd->runExecCmd(id);
        ExecCmd cmd = {
            id,
            nt17Cmd,
            std::make_shared<std::function<void ()>>([]() {}),
            std::make_shared<std::function<void (std::shared_ptr<InterfaceCmd> cmd)>>([](std::shared_ptr<InterfaceCmd> cmd) {})
        };
        cmds.push_back(cmd);
        qDebug() << "run";
    });
    QObject::connect(uint17.get(), &UINT17::stop, [serialPort, reppeterCmd, &cmds]() {
        std::shared_ptr<NT17Command> nt17Cmd = std::make_shared<NT17Command>();
        int id = reppeterCmd->appendExecCmd([nt17Cmd](){
            nt17Cmd;
        });
        reppeterCmd->runExecCmd(id);
        ExecCmd cmd = {
            id,
            nt17Cmd,
            std::make_shared<std::function<void ()>>([]() {qDebug() << "yes!"; }),
            std::make_shared<std::function<void (std::shared_ptr<InterfaceCmd> cmd)>>([](std::shared_ptr<InterfaceCmd> cmd) {
                NT17Command* nt17Cmd =  dynamic_cast<NT17Command*>(cmd.get());
                if (nt17Cmd) {
                    nt17Cmd->error();
                }
                //Изменение Device. Я бы вообще выкинул бы его. если не трубуется хранить состояние.
            })
        };
        (*cmd.errorFunc.get())(cmd.cmd);
        cmds.push_back(cmd);
        qDebug() << "stop";
    });
    //Нажал
    emit uint17->run();
    emit uint17->stop();

    return a.exec();
}

void reppeterCmd() {
    ReppeterCmd reppeterCmd;
    int id = reppeterCmd.appendExecCmd([](){ qDebug() << "I'm working"; });
    reppeterCmd.runExecCmd(id);
    QTimer::singleShot(0, [id, &reppeterCmd](){ reppeterCmd.removeExecCmd(id);});

    reppeterCmd.setReppet(10);
    for (int i = 0; i < 10; ++i) {
        int id = reppeterCmd.appendExecCmd([i](){ qDebug() << "I'm working i:" << i; });
        reppeterCmd.runExecCmd(id);
    }
}

class DeviceNT17 {
public:
    int a = 5;
};
