#include "nt17ui.h"

NT17UI::NT17UI(QObject *parent)
    : QObject{parent}
{

}

void NT17UI::setController(std::shared_ptr<NT17Controller> controller)
{
    connect(this, &NT17UI::run, controller.get(), &NT17Controller::start);
    connect(this, &NT17UI::stop, controller.get(), &NT17Controller::stop);
}

void NT17UI::setModel(int id, std::shared_ptr<NT17Model> model)
{
    this->id = id;
    this->model = model;
}

void NT17UI::update()
{
    NT17Model::Data data = model->getData(id);

    temp = data.temp;
}
