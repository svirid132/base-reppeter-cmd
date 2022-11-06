#ifndef UINT17_H
#define UINT17_H

#include "uint17controller.h"

#include <QObject>
#include <nt17model.h>

class UINT17 : public QObject
{
    Q_OBJECT
public:
    explicit UINT17(QObject *parent = nullptr);
    void setController(std::shared_ptr<UINT17Controller> controller);
    void setModel(int id, std::shared_ptr<NT17Model> model);
    void update();

signals:
    void run();
    void stop();

private:
    int id;
    std::shared_ptr<NT17Model> model;
    int temp;
};

#endif // UINT17_H
