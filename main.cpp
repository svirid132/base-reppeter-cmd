#include "reppetercmd.h"
#include "command/NT17Command.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReppeterCmd reppeterCmd;
    int id = reppeterCmd.appendExecCmd([](){ qDebug() << "I'm working"; });
    reppeterCmd.runExecCmd(id);
    QTimer::singleShot(0, [id, &reppeterCmd](){ reppeterCmd.removeExecCmd(id);});

    InterfaceCmd* nt17 = new NT17Command();
    reppeterCmd.setReppet(10);
    for (int i = 0; i < 10; ++i) {
        int id = reppeterCmd.appendExecCmd([i](){ qDebug() << "I'm working i:" << i; });
        reppeterCmd.runExecCmd(id);
    }

    return a.exec();
}
