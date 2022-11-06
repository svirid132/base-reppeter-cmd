#include "uint17.h"

UINT17::UINT17(QObject *parent)
    : QObject{parent}
{

}

void UINT17::setController(std::shared_ptr<UINT17Controller> controller)
{
    connect(this, &UINT17::run, controller.get(), &UINT17Controller::start);
    connect(this, &UINT17::stop, controller.get(), &UINT17Controller::stop);
}

void UINT17::setModel(int id, std::shared_ptr<NT17Model> model)
{
    this->id = id;
    this->model = model;
}

void UINT17::update()
{
    NT17Model::Data data = model->getData(id);

    temp = data.temp;
}
