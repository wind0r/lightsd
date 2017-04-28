#pragma once

#include <yaml-cpp/yaml.h>
#include "Operation.h"

#include "../VariableStore/VariableStore.h"
#include "../VariableStore/BoundConcreteValueType.h"


class GameOfLifeOperation : public Operation {
    bool initialized;
    size_t frame_counter;

    BoundConcreteValue<float> default_hue;
    BoundConcreteValue<float> default_saturation;
    BoundConcreteValue<float> default_value;

    BoundConcreteValue<bool> v0;
    BoundConcreteValue<bool> v1;
    BoundConcreteValue<bool> v2;
    BoundConcreteValue<bool> v3;
    BoundConcreteValue<bool> v4;
    BoundConcreteValue<bool> v5;
    BoundConcreteValue<bool> v6;
    BoundConcreteValue<bool> v7;



    std::vector<HSV> output;
    std::vector<HSV> delta;

public:

    GameOfLifeOperation(VariableStore &store, YAML::const_iterator start, YAML::const_iterator end);
    virtual ~GameOfLifeOperation() {}
    void update(const Config* const);
    virtual BufferType operator()(BufferType &buffer);
};

