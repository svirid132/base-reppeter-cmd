#include "nt17model.h"

#include <algorithm>

NT17Model::NT17Model()
{
    datas.resize(10);

    int id = 1;
    std::for_each(datas.begin(), datas.end(), [&id](Data data) {
        data.id = id;
        id += 1;
    });
}

void NT17Model::setUpdateFunc(std::function<void (int id)> updateFunc)
{
    this->updateFunc = updateFunc;
}

void NT17Model::updateData(NT17Model::Data data)
{
    auto it = std::find_if(datas.begin(), datas.end(), [data](Data m_data) {
        if (data.id == m_data.id) {
            return true;
        }
        return false;
    });
    if (it == datas.end()) {
        return;
    }

    *it = data;
    updateFunc(it->id);
}

NT17Model::Data NT17Model::getData(int id)
{
    auto it = std::find_if(datas.begin(), datas.end(), [id](Data m_data) {
        if (id == m_data.id) {
            return true;
        }
        return false;
    });
    return *it;
}
