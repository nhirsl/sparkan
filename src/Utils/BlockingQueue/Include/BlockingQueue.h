#pragma once

#include "QueueOperationStatusEnum.h"

template<typename _Value_type>
class BlockingQueue {
public:
    BlockingQueue() = default;
    
    virtual ~BlockingQueue() = default;

    virtual QueueOperationStatus PushFront(const _Value_type& value) = 0;
    
    virtual QueueOperationStatus PushBack(const _Value_type& value) = 0;
    
    virtual QueueOperationStatus TryPushFront(const _Value_type& value) = 0;
    
    virtual QueueOperationStatus TryPushBack(const _Value_type& value) = 0;
    
    virtual QueueOperationStatus NonblockingPushFront(const _Value_type& value) = 0;
    
    virtual QueueOperationStatus NonblockingPushBack(const _Value_type& value) = 0;   
    
    virtual QueueOperationStatus PopFront(_Value_type* value) = 0;
    
    virtual QueueOperationStatus PopBack(_Value_type* value) = 0;
    
    virtual QueueOperationStatus TryPopFront(_Value_type* value) = 0;
    
    virtual QueueOperationStatus TryPopBack(_Value_type* value) = 0;
    
    virtual QueueOperationStatus NonblockingPopFront(_Value_type* value) = 0;
    
    virtual QueueOperationStatus NonblockingPopBack(_Value_type* value) = 0;
    
    virtual void Close() = 0;
    
    virtual bool IsClosed() = 0;
    
    virtual bool IsEmpty() = 0;
    
    virtual bool IsFull() = 0;
    
    virtual size_t Size() = 0;
};
