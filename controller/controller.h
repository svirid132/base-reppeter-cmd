#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <command/interfacecmd.h>

#include <QSerialPort>
#include <QTimer>

struct ExecCmd {
    int id;
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
    };

    void setProps(const Props& props);
    //Обработка responce запроса
    void setting();

protected:
    int getId();
    void runExecCmd(std::shared_ptr<ExecCmd> execCmd);

private:
    static int idCmd;
    static std::vector<std::shared_ptr<ExecCmd>> execCmds;
    Props props;
    struct RepeterCmd {
        int repete = 0;
        std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();
    };
    std::shared_ptr<std::function<void()>> deleteCmdFunc(int id, std::shared_ptr<RepeterCmd> repeterCmd);
};

#endif // CONTROLLER_H
