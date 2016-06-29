#include "BlockingQueueFactory.h"

BlockingQueueFactoryWPtr BlockingQueueFactory::instance;

std::mutex BlockingQueueFactory::mutex;

BlockingQueueFactoryPtr BlockingQueueFactory::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    BlockingQueueFactoryPtr blockingQueueFactory = instance.lock();
    if (blockingQueueFactory == nullptr) {
        blockingQueueFactory.reset(new BlockingQueueFactory());
        instance = blockingQueueFactory;
    }
    return blockingQueueFactory;
}
