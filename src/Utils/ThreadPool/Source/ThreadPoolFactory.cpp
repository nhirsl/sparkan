#include "ThreadPoolFactory.h"

#include "FixedThreadPool.h"

ThreadPoolFactoryWPtr ThreadPoolFactory::instance;

std::mutex ThreadPoolFactory::mutex;

ThreadPoolFactoryPtr ThreadPoolFactory::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    ThreadPoolFactoryPtr threadPoolFactory = instance.lock();
    if(threadPoolFactory == nullptr) {
        threadPoolFactory.reset(new ThreadPoolFactory());
        instance = threadPoolFactory;
    }
    return threadPoolFactory;
}

ThreadPoolUPtr ThreadPoolFactory::CreateFixedThreadPool(size_t numberOfThreads) {
    FixedThreadPoolUPtr fixedThreadPool(new FixedThreadPool(numberOfThreads));
    return std::move(fixedThreadPool);
}
