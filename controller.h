#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "reppetercmd.h"

#include <command/interfacecmd.h>

#include <QSerialPort>

struct ExecCmd {
    int id;
    int idReppeter;
    std::shared_ptr<InterfaceCmd> cmd;
    std::shared_ptr<std::function<void ()>> succesFunc;
    std::shared_ptr<std::function<void (std::shared_ptr<InterfaceCmd> cmd)>> errorFunc;
};

class Controller
{
public:
    Controller();

    struct Props {
        std::shared_ptr<QSerialPort> serialPort;
        std::shared_ptr<ReppeterCmd> reppeterCmd;
        std::vector<std::shared_ptr<ExecCmd>> cmds;
    };

    void setProps(const Props& props);

protected:
    int getId();
    void runExecCmd(std::shared_ptr<ExecCmd> execCmd);

private:
    static int idCmd;
    Props props;
};

#endif // CONTROLLER_H
