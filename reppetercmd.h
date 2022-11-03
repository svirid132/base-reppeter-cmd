#ifndef REPPETERCMD_H
#define REPPETERCMD_H
#include <QTimer>
#include <functional>
#include <memory>

class ReppeterCmd
{
public:
    ReppeterCmd();
    void setReppet(int reppet);
    //Берет на выполнение функцию, возращает ее id
    int appendExecCmd(std::function<void()> execCmd);
    //Запускает cb execCmd по id выданому appendExecCmd,
    //и повторяет отправку до reppet или пока execCmd не будет удален через removeExecCmd
    bool runExecCmd(int id);
    //удаляет команду на выполнение.
    //в параметрах id - это id выданное appendExecCmd
    bool removeExecCmd(int id);

private:
    int nextIdCmd = 1;
    int reppet = 3;

    struct ReppetCmd {
        int id;
        int countReppet = 0;
        std::function<void()> execCmd;
        std::unique_ptr<QTimer> timer = std::make_unique<QTimer>();
    };
    std::map<int, std::shared_ptr<ReppetCmd>> reppetCmds;
};

#endif // REPPETERCMD_H
