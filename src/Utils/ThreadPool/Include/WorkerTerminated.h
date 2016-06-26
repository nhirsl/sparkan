#pragma once

#include <string>
#include <stdexcept>

class WorkerTerminated : public std::runtime_error {
public:
    WorkerTerminated() 
        : WorkerTerminated("") {
    }
    
    WorkerTerminated(std::string what) 
        : std::runtime_error(std::move(what)) {
    }
};
