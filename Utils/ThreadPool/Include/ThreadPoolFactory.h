#pragma once

#include "ForwardDeclarations.h"

#include <mutex>
#include <thread>

class ThreadPoolFactory {
public:
    static ThreadPoolFactoryPtr GetInstance();
    
    ThreadPoolUPtr CreateFixedThreadPool(size_t numberOfThreads = std::thread::hardware_concurrency());
    
private:
    ThreadPoolFactory() = default;
    
    static ThreadPoolFactoryWPtr instance;
    
    static std::mutex mutex;
};
