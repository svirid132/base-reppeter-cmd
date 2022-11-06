#ifndef NT17MODEL_H
#define NT17MODEL_H

#include <vector>
#include <functional>

class NT17Model
{
public:
    NT17Model();
    void setUpdateFunc(std::function<void(int id)> updateFunc);

    struct Data {
        int id;
        int temp = 0;
        bool working = false;
    };
    void updateData(NT17Model::Data Data);
    Data getData(int id);

private:
    std::vector<Data> datas;
    std::function<void(int id)> updateFunc;
};

#endif // NT17MODEL_H
