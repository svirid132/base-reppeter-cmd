#include "responcehandler.h"

ResponceHandler::ResponceHandler()
{

}

void ResponceHandler::setProps(const Props &props)
{
    this->props = props;
}

void ResponceHandler::setting()
{
    QObject::connect(props.serialPort.get(), &QSerialPort::readyRead, [this]() {
        Props props = this->props;
        QByteArray byteRes = props.serialPort->readAll();
        auto it = std::find_if(props.cmds.begin(), props.cmds.end(), [byteRes](std::shared_ptr<ExecCmd> execCmd) {
            if (execCmd->cmd->isResAddress(byteRes) && execCmd->cmd->isResEquivalent(byteRes)) {
                return true;
            }
            return false;
        });
        if (it == props.cmds.end()) {
            return;
        }
        (((*it).get())->succesFunc.get());
        props.reppeterCmd->removeExecCmd((*it)->idReppeter);
        props.cmds.erase(it);
    });
}
