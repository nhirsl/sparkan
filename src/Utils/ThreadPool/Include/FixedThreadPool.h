#pragma once

#include "ThreadPool.h"

#include <vector>
#include <memory>
#include <thread>

#include "BlockingQueue.h"

using TaskBlockingQueueUPtr = std::unique_ptr<BlockingQueue<TaskPtr>>;

class FixedThreadPool : public ThreadPool {
public:
    FixedThreadPool(size_t numberOfThreads, TaskBlockingQueueUPtr blockingQueue);
    
    virtual ~FixedThreadPool();

    virtual void Start() override;
    
    virtual void Close() override;
    
    virtual void Enqueue(TaskPtr task) override;
    
    virtual void Urgent(TaskPtr task) override;
    
private:
    void WorkerFunction();
    void JoinThreads();
    
    size_t mNumberOfThreads;
    TaskBlockingQueueUPtr mTaskQueue;
    std::vector<std::thread> mThreads;
};
