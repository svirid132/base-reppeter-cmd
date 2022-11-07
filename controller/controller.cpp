#include "controller.h"

Controller::Controller()
{

}

int Controller::getId()
{
    int id = idCmd;
    idCmd += 1;
    return id;
}

void Controller::setProps(const Props& props)
{
    this->props = props;
}

void Controller::setting()
{
    QObject::connect(props.serialPort.get(), &QSerialPort::readyRead, [this]() {
        Props props = this->props;
        QByteArray byteRes = props.serialPort->readAll();
        auto it = std::find_if(execCmds.begin(), execCmds.end(), [byteRes](std::shared_ptr<ExecCmd> execCmd) {
            if (execCmd->cmd->isResAddress(byteRes) && execCmd->cmd->isResEquivalent(byteRes)) {
                return true;
            }
            return false;
        });
        if (it == execCmds.end()) {
            return;
        }
        (*(*it)->succesFunc)();
        execCmds.erase(it);
    });
}

void Controller::runExecCmd(std::shared_ptr<ExecCmd> execCmd)
{
    int id = execCmd->id;
    auto succesFunc = *execCmd->succesFunc;
    auto errorFunc = *execCmd->errorFunc;
    std::shared_ptr<RepeterCmd> repeterCmd = std::make_shared<RepeterCmd>();
    std::shared_ptr<std::function<void()>> deleteCmd = deleteCmdFunc(id, repeterCmd);

    *execCmd->succesFunc = [succesFunc, deleteCmd]() {
        succesFunc();
        (*deleteCmd)();
    };
    *execCmd->errorFunc = [errorFunc, deleteCmd](std::shared_ptr<InterfaceCmd> cmd) {
        errorFunc(cmd);
        (*deleteCmd)();
    };
    execCmds.push_back(execCmd);

    //Запуск команды
    auto sendCmd = [execCmd, repeterCmd, deleteCmd]() {
        //SerialPort send execCmd.cmd
        if (repeterCmd->repete >= 3) {
            (*deleteCmd)();
            return;
        }
        repeterCmd->repete += 1;
    };
    QObject::connect(repeterCmd->timer.get(), &QTimer::timeout, sendCmd);
    repeterCmd->timer->setInterval(1000);
    repeterCmd->timer->start();
    sendCmd();
}

std::shared_ptr<std::function<void()>> Controller::deleteCmdFunc(int id, std::shared_ptr<RepeterCmd> repeterCmd)
{
    std::shared_ptr<std::function<void ()> > func = std::make_shared<std::function<void()>>([this, id, repeterCmd]() {
        auto it = std::find_if(execCmds.begin(), execCmds.end(), [id](std::shared_ptr<ExecCmd> cmd) {
            if (cmd->id == id) {
                return true;
            }
            return false;
        });
        if(it == execCmds.end()) {
            return;
        }
        repeterCmd->timer->disconnect();
        repeterCmd->timer->stop();
        execCmds.erase(it);
        qDebug() << "delete id" << id;
    });

    return func;
}

int Controller::idCmd = 1;
std::vector<std::shared_ptr<ExecCmd>> Controller::execCmds = std::vector<std::shared_ptr<ExecCmd>>();

