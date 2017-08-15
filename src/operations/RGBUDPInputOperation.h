#pragma once

#include "Operation.h"


#include <yaml-cpp/yaml.h>

#include "VariableStore/VariableStore.h"
#include "VariableStore/BoundConcreteValueType.h"


#include "net/RGBUDPSink.h"

class RGBUDPInputOperation : public Operation {

    RGBUDPSink sink;
public:
    RGBUDPInputOperation(const std::string& name, VariableStore &store, YAML::const_iterator start, YAML::const_iterator end);

    ~RGBUDPInputOperation();

    Operation::BufferType operator()(Operation::BufferType &buffer);

};