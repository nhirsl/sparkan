<<<<<<< HEAD
#include "ThreadPoolFactory.h"

#include "FixedThreadPool.h"

#include "BlockingQueueFactory.h"
#include "BlockingQueue.h"
=======
#include "ThreadPool/ThreadPoolFactory.h"

#include "FixedThreadPool.h"

#include "BlockingQueue/BlockingQueueFactory.h"
#include "BlockingQueue/BlockingQueue.h"
>>>>>>> nebojsakaran

using TaskBlockingQueueUPtr = std::unique_ptr<BlockingQueue<TaskPtr>>;

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
    BlockingQueueFactoryPtr blockingQueueFactory = BlockingQueueFactory::GetInstance();
    if (blockingQueueFactory) {
        TaskBlockingQueueUPtr blockingQueue = blockingQueueFactory->CreateInstance<TaskPtr>();
        if (blockingQueue) {
            FixedThreadPoolUPtr fixedThreadPool(new FixedThreadPool(numberOfThreads, std::move(blockingQueue)));
            return std::move(fixedThreadPool);
        }
    }
    return nullptr;
}
