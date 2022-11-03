#ifndef INTERFACECMD_H
#define INTERFACECMD_H

#include <QByteArray>

class InterfaceCmd
{
public:
    InterfaceCmd();

//Ответ response
    //Если адрес сходится
    virtual bool isResAddress(const QByteArray& resCmd) = 0;
    //Если запрос эквивалентен тому, что мы отправили. Там могут быть ошибки.
    virtual bool isResEquivalent(const QByteArray& resCmd) = 0;
};

#endif // INTERFACECMD_H
