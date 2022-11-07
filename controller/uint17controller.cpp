#include "model/nt17model.h"
#include "nt17controller.h"

#include <command/nt17command.h>

NT17Controller::NT17Controller(int id, std::shared_ptr<NT17Model> model, QObject *parent)
    : QObject{parent}
{
    m_id = id;
    m_model = model;
}

void NT17Controller::start()
{
    std::shared_ptr<NT17Command> nt17Cmd = std::make_shared<NT17Command>();
    std::shared_ptr<ExecCmd> execCmd = std::make_shared<ExecCmd>(ExecCmd{
        getId(),
        nt17Cmd,
        std::make_shared<std::function<void ()>>([this]() {
            NT17Model::Data data = m_model->getData(m_id);
            data.working = true;
            m_model->updateData(data);
        }),
        std::make_shared<std::function<void (std::shared_ptr<InterfaceCmd> cmd)>>([](std::shared_ptr<InterfaceCmd> cmd) {})
    });

    Controller::runExecCmd(execCmd);

    qDebug() << "run";
}

void NT17Controller::stop()
{
    std::shared_ptr<NT17Command> nt17Cmd = std::make_shared<NT17Command>();
    std::shared_ptr<ExecCmd> execCmd = std::make_shared<ExecCmd>(ExecCmd{
        getId(),
        nt17Cmd,
        std::make_shared<std::function<void ()>>([]() {qDebug() << "yes!"; }),
        std::make_shared<std::function<void (std::shared_ptr<InterfaceCmd> cmd)>>([](std::shared_ptr<InterfaceCmd> cmd) {
            NT17Command* nt17Cmd =  dynamic_cast<NT17Command*>(cmd.get());
            if (nt17Cmd) {
                nt17Cmd->error();
            }
        })
    });

    Controller::runExecCmd(execCmd);

    qDebug() << "stop";
}


