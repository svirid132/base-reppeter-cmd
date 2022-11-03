#ifndef NT17COMMAND_H
#define NT17COMMAND_H

#include "interfacecmd.h"

#include <QDebug>

class NT17Command : public InterfaceCmd
{
public:
    NT17Command();

    //Если запрос эквивалентен тому, что мы отправили. Там могут быть ошибки.
    struct ErrorNT17;
    bool isResAddress(const QByteArray& resCmd) { return true; };
    bool isResEquivalent(const QByteArray& resCmd) {
        qDebug() << "this is NT17";
        return true;
    };
};

#endif // NT17COMMAND_H
