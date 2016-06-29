#pragma once

#include "BlockingQueue.h"

#include "NonblockingRecursiveLock.h"

#include <mutex>
#include <condition_variable>
#include <deque>
#include <cassert>

template<typename _Element_type>
class SizeUnlimitedBlockingQueue : public BlockingQueue<_Element_type> {
public:
    SizeUnlimitedBlockingQueue() 
        : mClosed(false) {
    }
    
    ~SizeUnlimitedBlockingQueue() {
        assert(IsClosed());
    }
    
    QueueOperationStatus PushBack(const _Element_type& element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if(mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            mQueue.push_back(element);
            mQueueIsNotEmpty.notify_all();
            return QueueOperationStatus::SUCCESS;
        }
    }
    
    QueueOperationStatus PushFront(const _Element_type& element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if(mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            mQueue.push_front(element);
            mQueueIsNotEmpty.notify_all();
            return QueueOperationStatus::SUCCESS;
        }
    }
        
    QueueOperationStatus TryPushBack(const _Element_type& element) override {
        return PushBack(element);
    }
    
    QueueOperationStatus TryPushFront(const _Element_type& element) override {
        return PushFront(element);
    }
    
    QueueOperationStatus PopFront(_Element_type* element) override {
        std::unique_lock<std::recursive_mutex> lock(mMutex);
        
        while(mClosed == false && mQueue.size() == 0) {
            mQueueIsNotEmpty.wait<std::unique_lock<std::recursive_mutex>>(lock);
        }
        
        if(mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            *element = mQueue.front();
            mQueue.pop_front();
            return QueueOperationStatus::SUCCESS;            
        }
    }
    
    QueueOperationStatus PopBack(_Element_type* element) override {
        std::unique_lock<std::recursive_mutex> lock(mMutex);

        while(mClosed == false && mQueue.size() == 0) {
            mQueueIsNotEmpty.wait<std::unique_lock<std::recursive_mutex>>(lock);
        }
        
        if(mClosed) {
            return QueueOperationStatus::CLOSED;
        } else {
            *element = mQueue.back();
            mQueue.pop_back();
            return QueueOperationStatus::SUCCESS;            
        }        
    }
    
    QueueOperationStatus TryPopFront(_Element_type* element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if(mQueue.size() == 0) {
           return QueueOperationStatus::EMPTY;
        } else {
            *element = mQueue.front();
            mQueue.pop_front();
            return QueueOperationStatus::SUCCESS;
        }
    }
    
    QueueOperationStatus TryPopBack(_Element_type* element) override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if(mQueue.size() == 0) {
           return QueueOperationStatus::EMPTY;
        } else {
            *element = mQueue.back();
            mQueue.pop_back();
            return QueueOperationStatus::SUCCESS;
        }
    }
    
    QueueOperationStatus NonblockingPopBack(_Element_type* element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            if(mClosed) {
                return QueueOperationStatus::CLOSED;
            } else {
                *element = mQueue.back();
                mQueue.pop_back();
                return QueueOperationStatus::SUCCESS;                
            }
        } else {
            return QueueOperationStatus::BUSY;
        }
    }
    
    QueueOperationStatus NonblockingPopFront(_Element_type* element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            if(mClosed) {
                return QueueOperationStatus::CLOSED;
            } else {
                *element = mQueue.front();
                mQueue.pop_front();
                return QueueOperationStatus::SUCCESS;                
            }
        } else {
            return QueueOperationStatus::BUSY;
        }
    }
    
    QueueOperationStatus NonblockingPushBack(const _Element_type& element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            if(mClosed) {
                return QueueOperationStatus::CLOSED;
            } else {
                mQueue.push_back(element);
                mQueueIsNotEmpty.notify_all();
                return QueueOperationStatus::SUCCESS;
            }
        } else {
            return QueueOperationStatus::BUSY;
        }
    }

    QueueOperationStatus NonblockingPushFront(const _Element_type& element) override {
        NonblockingRecursiveLock lock(mMutex);
        if(lock.TryLock()) {
            if(mClosed) {
                return QueueOperationStatus::CLOSED;
            } else {
                mQueue.push_front(element);
                mQueueIsNotEmpty.notify_all();
                return QueueOperationStatus::SUCCESS;
            }
        } else {
            return QueueOperationStatus::BUSY;
        }
    }
    
    void Close() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        mClosed = true;
        mQueue.clear();
        mQueueIsNotEmpty.notify_all();
    }
    
    bool IsClosed() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mClosed;
    }
    
    bool IsEmpty() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mQueue.size() == 07;
    }
    
    bool IsFull() override {
        return false;
    }
    
    size_t Size() override {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return mQueue.size();
    }
    
private:
    bool mClosed;
    std::recursive_mutex mMutex;
    std::deque<_Element_type> mQueue;
    std::condition_variable_any mQueueIsNotEmpty;
};
