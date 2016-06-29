#pragma once

#include "QueueOperationStatusEnum.h"

template<typename _Element_type>
class BlockingQueue {
public:
    BlockingQueue() = default;
    
    virtual ~BlockingQueue() = default;

    virtual QueueOperationStatus PushFront(const _Element_type& element) = 0;
    
    virtual QueueOperationStatus PushBack(const _Element_type& element) = 0;
    
    virtual QueueOperationStatus TryPushFront(const _Element_type& element) = 0;
    
    virtual QueueOperationStatus TryPushBack(const _Element_type& element) = 0;
    
    virtual QueueOperationStatus NonblockingPushFront(const _Element_type& element) = 0;
    
    virtual QueueOperationStatus NonblockingPushBack(const _Element_type& element) = 0;   
    
    virtual QueueOperationStatus PopFront(_Element_type* element) = 0;
    
    virtual QueueOperationStatus PopBack(_Element_type* element) = 0;
    
    virtual QueueOperationStatus TryPopFront(_Element_type* element) = 0;
    
    virtual QueueOperationStatus TryPopBack(_Element_type* element) = 0;
    
    virtual QueueOperationStatus NonblockingPopFront(_Element_type* element) = 0;
    
    virtual QueueOperationStatus NonblockingPopBack(_Element_type* element) = 0;
    
    virtual void Close() = 0;
    
    virtual bool IsClosed() = 0;
    
    virtual bool IsEmpty() = 0;
    
    virtual bool IsFull() = 0;
    
    virtual size_t Size() = 0;
};
