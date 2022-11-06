#ifndef RESPONCEHANDLER_H
#define RESPONCEHANDLER_H

#include "controller.h"
#include "reppetercmd.h"

#include <QSerialPort>

class ResponceHandler
{
public:
    ResponceHandler();

    struct Props {
        std::shared_ptr<QSerialPort> serialPort;
        std::shared_ptr<ReppeterCmd> reppeterCmd;
        std::vector<std::shared_ptr<ExecCmd>> cmds;
    };

    void setProps(const Props& props);
    void setting();

private:
    Props props;
};

#endif // RESPONCEHANDLER_H
