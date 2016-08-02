#pragma once

#include "ForwardDeclarations.h"

class ThreadPool {
public:
    ThreadPool() = default;
    
    virtual ~ThreadPool() = default;
  
    virtual void Start() = 0;
    
    virtual void Close() = 0;
    
    virtual void Enqueue(TaskPtr task) = 0;
    
    virtual void Urgent(TaskPtr task) = 0;
};
