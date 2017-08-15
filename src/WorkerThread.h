#pragma once

#include <mutex>
#include "config.h"
#include "FrameScheduler.h"

class WorkerThread {
    bool doRun;
    ConfigPtr config_ptr;
    ConfigPtr new_config_ptr;
    std::mutex config_mutex;

public:
    WorkerThread();

    void setConfig(ConfigPtr cfg);

    ConfigPtr getConfig();

    void run();
};