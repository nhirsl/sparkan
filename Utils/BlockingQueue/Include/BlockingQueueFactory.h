#pragma once

#include "ForwardDeclarations.h"

#include "BlockingQueue.h"
#include "SizeLimitedBlockingQueue.h"
#include "SizeUnlimitedBlockingQueue.h"

#include <mutex>

class BlockingQueueFactory final {
public:    
    virtual ~BlockingQueueFactory() = default;
    
    static BlockingQueueFactoryPtr GetInstance();
    
    template<typename _Element_type>
    std::unique_ptr<BlockingQueue<_Element_type>> CreateInstance() {
        std::unique_ptr<BlockingQueue<_Element_type>> blockingQueue(new SizeUnlimitedBlockingQueue<_Element_type>());
        return std::move(blockingQueue);
    }
    
    template<typename _Element_type>
    std::unique_ptr<BlockingQueue<_Element_type>> CreateInstance(size_t upperLimit) {
        std::unique_ptr<BlockingQueue<_Element_type>> blockingQueue(new SizeLimitedBlockingQueue<_Element_type>(upperLimit));
        return std::move(blockingQueue);
    }
    
private:
    BlockingQueueFactory() = default;
    
    static BlockingQueueFactoryWPtr instance;
    
    static std::mutex mutex;
};
