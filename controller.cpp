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


void Controller::runExecCmd(std::shared_ptr<ExecCmd> execCmd)
{
    props.cmds.push_back(execCmd);
    int idReppeter = props.reppeterCmd->appendExecCmd([](){
        //Настроиваем команду
        //Тут создание команды. И ее отправка через QSerialPort
    },
    [this, execCmd]() {
        //Удаление команды
        auto it = std::find(this->props.cmds.begin(), this->props.cmds.end(), execCmd);
        if (it == this->props.cmds.end()) {
            qDebug() << "dont find it";
            return;
        }
        this->props.cmds.erase(it);
    });
    execCmd->idReppeter = idReppeter;
    props.reppeterCmd->runExecCmd(idReppeter);
}

int Controller::idCmd = 1;

