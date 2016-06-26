#pragma once

#include "ForwardDeclarations.h"

class ThreadPool {
public:
    ThreadPool() = default;
    virtual ~ThreadPool() = default;
  
    virtual void Start() = 0;
    virtual void Terminate() = 0;
    
    virtual void Enqueue(Task task) = 0;
    virtual void Urgent(Task task) = 0;
};
