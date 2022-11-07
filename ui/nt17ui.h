#ifndef NT17UI_H
#define NT17UI_H

#include "controller/nt17controller.h"

#include <QObject>
#include "model/nt17model.h"

class NT17UI : public QObject
{
    Q_OBJECT
public:
    explicit NT17UI(QObject *parent = nullptr);
    void setController(std::shared_ptr<NT17Controller> controller);
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
