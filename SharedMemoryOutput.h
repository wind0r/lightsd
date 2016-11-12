//
// Created by andi on 11/12/16.
//

#ifndef LIGHTSD_SHAREDMEMORYOUTPUT_H
#define LIGHTSD_SHAREDMEMORYOUTPUT_H

#include "SharedMemoryBuffer.h"
#include "Output.h"

class SharedMemoryOutput : public Output {
    SharedMemoryBuffer shmBuffer;
    const std::string filename;


public:
    SharedMemoryOutput(const YAML::Node &params);

    virtual ~SharedMemoryOutput() {};
    virtual void draw(const AbstractBaseBuffer<HSV> &buffer);
    virtual void draw(const std::vector<HSV>& buffer);
};

#endif //LIGHTSD_SHAREDMEMORYOUTPUT_H