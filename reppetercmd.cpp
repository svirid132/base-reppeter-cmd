#include "reppetercmd.h"
#include <QDebug>
#include <QObject>

ReppeterCmd::ReppeterCmd()
{

}

void ReppeterCmd::setReppet(int reppet)
{
    this->reppet = reppet;
}

int ReppeterCmd::appendExecCmd(std::function<void ()>&& execCmd, std::function<void()>&& deleteCmd)
{
    std::shared_ptr<ReppetCmd> reppetCmd = std::make_shared<ReppetCmd>();
    reppetCmd->id = nextIdCmd;
    nextIdCmd += 1;
    reppetCmd->execCmd = std::forward<std::function<void ()>>(execCmd);
    reppetCmd->deleteCmd = std::forward<std::function<void ()>>(deleteCmd);
    reppetCmd->timer->setInterval(1000);
    QObject::connect(reppetCmd->timer.get(), &QTimer::timeout, [this, reppetCmd]() {
        if (reppetCmd->countReppet == 3) {
            this->removeExecCmd(reppetCmd->id);
            return;
        }
        reppetCmd->execCmd();
        reppetCmd->countReppet += 1;
    });
    reppetCmds.insert(std::pair{reppetCmd->id, reppetCmd});

    return reppetCmd->id;
}

bool ReppeterCmd::runExecCmd(int id)
{
    if (reppetCmds.find(id) == reppetCmds.end()) {
        return false;
    }

    reppetCmds[id]->execCmd();
    reppetCmds[id]->countReppet += 1;
    reppetCmds[id]->timer->start();
    return true;
}

bool ReppeterCmd::removeExecCmd(int id)
{
    auto it = reppetCmds.find(id);
    if (it == reppetCmds.end()) {
        return false;
    }

    //удаление переданное при добавлении команды
    it->second->deleteCmd();
    //Чтобы уничтожились shared_ptr
    it->second->timer->disconnect();
    //Проверить, удаление timer
    int _id = it->second->id;
    QObject::connect(it->second->timer.get(), &QTimer::destroyed, [_id]() {
        qDebug() << "deleted cmd on id:" << _id;
    });
    reppetCmds.erase(it);

    return true;
}


