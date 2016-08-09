#pragma once

#include "BlockingQueue/BlockingQueue.h"

#include "NonblockingRecursiveLock.h"

#include <mutex>
#include <condition_variable>
#include <deque>
#include <cassert>

template<typename _Element_type>
class SizeLimitedBlockingQueue : public BlockingQueue<_Element_type> {
public:
    SizeLimitedBlockingQueue(size_t upperLimit)
        : mUpperLimit(upperLimit)
        , mClosed(false) {
    }
    
    ~SizeLimitedBlockingQueue() {
        assert(IsClosed());
    }
    
    QueueOperationStatus PushFront(_Element_type element) override {
        std::unique_lock<std::recursive_mutex> lock(mMutex);
        
        while (mClosed == false && mQueue.size() >= mUpperLimit) {
            mQueueIsNotFull.wait<std::unique_lock<std::recursive_mutex>>(lock);
        }
        
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            mQueue.push_front(std::move(element));
            mQueueIsNotEmpty.notify_all();
            return QueueOperationStatus::SUCCESS;
        }
    }
    
    QueueOperationStatus PushBack(_Element_type element) override {
        std::unique_lock<std::recursive_mutex> lock(mMutex);
        
        while (mClosed == false && mQueue.size() >= mUpperLimit) {
            mQueueIsNotFull.wait<std::unique_lock<std::recursive_mutex>>(lock);
        }
        
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            mQueue.push_back(std::move(element));
            mQueueIsNotEmpty.notify_all();
            return QueueOperationStatus::SUCCESS;
        }        
    }
    
    QueueOperationStatus TryPushFront(_Element_type element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            if(mQueue.size() >= mUpperLimit) {
                return QueueOperationStatus::FULL;
            } else {
                mQueue.push_front(std::move(element));
                mQueueIsNotEmpty.notify_all();
                return QueueOperationStatus::SUCCESS;
            }
        }
    }
    
    QueueOperationStatus TryPushBack(_Element_type element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            if(mQueue.size() >= mUpperLimit) {
                return QueueOperationStatus::FULL;
            } else {
                mQueue.push_back(std::move(element));
                mQueueIsNotEmpty.notify_all();
                return QueueOperationStatus::SUCCESS;
            }        
        }
    }
    
    QueueOperationStatus NonblockingPushFront(_Element_type element) override {
        NonblockingRecursiveLock lock(mMutex);
        if (lock.TryLock()) {
            return TryPushFront(std::move(element));
        } else {
            return QueueOperationStatus::BUSY;
        }
    }
    
    QueueOperationStatus NonblockingPushBack(_Element_type element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            return TryPushBack(std::move(element));
        } else {
            return QueueOperationStatus::BUSY;
        }        
    }
    
    QueueOperationStatus PopFront(_Element_type* element) override {
        std::unique_lock<std::recursive_mutex> lock(mMutex);
        
        while (mClosed == false && mQueue.size() == 0) {
            mQueueIsNotEmpty.wait<std::unique_lock<std::recursive_mutex>>(lock);
        }
        
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            *element = mQueue.front();
            mQueue.pop_front();
            mQueueIsNotFull.notify_all();
            return QueueOperationStatus::SUCCESS;
        }
    }
    
    QueueOperationStatus PopBack(_Element_type* element) override {
        std::unique_lock<std::recursive_mutex> lock(mMutex);
        
        while(mClosed == false && mQueue.size() == 0) {
            mQueueIsNotEmpty.wait<std::unique_lock<std::recursive_mutex>>(lock);
        }
        
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            *element = mQueue.back();
            mQueue.pop_back();
            mQueueIsNotFull.notify_all();
            return QueueOperationStatus::SUCCESS;
        }        
    }
    
    QueueOperationStatus TryPopFront(_Element_type* element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            if (mQueue.size() == 0) {
                return QueueOperationStatus::EMPTY;
            } else {
                *element = mQueue.front();
                mQueue.pop_front();
                mQueueIsNotFull.notify_all();
                return QueueOperationStatus::SUCCESS;            
            }
        }
    }
    
    QueueOperationStatus TryPopBack(_Element_type* element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if (mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            if (mQueue.size() == 0) {
                return QueueOperationStatus::EMPTY;
            } else {
                *element = mQueue.back();
                mQueue.pop_back();
                mQueueIsNotFull.notify_all();
                return QueueOperationStatus::SUCCESS;            
            }        
        }
    }
    
    QueueOperationStatus NonblockingPopFront(_Element_type* element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            return TryPopFront(element);
        } else {
            return QueueOperationStatus::BUSY;
        }        
    }
    
    QueueOperationStatus NonblockingPopBack(_Element_type* element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            return TryPopBack(element);
        } else {
            return QueueOperationStatus::BUSY;
        }        
    }
    
    void Close() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        mClosed = true;
        mQueue.clear();
        mQueueIsNotEmpty.notify_all();
        mQueueIsNotFull.notify_all();
    }
    
    bool IsClosed() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mClosed;
    }
    
    bool IsEmpty() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mQueue.size() == 0;
    }
    
    bool IsFull() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mQueue.size() == mUpperLimit;
    }
    
    size_t Size() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mQueue.size();
    }
    
private:
    size_t mUpperLimit;
    bool mClosed;
    std::recursive_mutex mMutex;
    std::deque<_Element_type> mQueue;
    std::condition_variable_any mQueueIsNotEmpty;
    std::condition_variable_any mQueueIsNotFull;
};
