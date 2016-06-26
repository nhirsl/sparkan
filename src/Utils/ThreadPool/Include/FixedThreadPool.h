#pragma once

#include "ThreadPool.h"

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <deque>

class FixedThreadPool : public ThreadPool {
public:
    FixedThreadPool(size_t numberOfThread);
    virtual ~FixedThreadPool();

    virtual void Start() override;
    virtual void Terminate() override;
    
    virtual void Enqueue(Task task) override;
    virtual void Urgent(Task task) override;
    
private:
    void WorkerFunction();
    
    void PushBack(Task task);
    void PushFront(Task task);
    Task GetNext();
    
    size_t mNumberOfThreads;
    
    std::mutex mMutex;
    
    std::condition_variable mQueueIsNotEmpty;
    
    bool mTerminated;
    
    std::deque<Task> mQueue;
    
    std::vector<std::thread> mThreads;
};
