#pragma once

#include "ThreadPool.h"

#include <vector>
#include <memory>
#include <thread>

#include "BlockingQueue.h"

using TaskBlockingQueueUPtr = std::unique_ptr<BlockingQueue<Task>>;

class FixedThreadPool : public ThreadPool {
public:
    FixedThreadPool(size_t numberOfThreads, TaskBlockingQueueUPtr blockingQueue);
    
    virtual ~FixedThreadPool();

    virtual void Start() override;
    
    virtual void Close() override;
    
    virtual void Enqueue(Task task) override;
    
    virtual void Urgent(Task task) override;
    
private:
    void WorkerFunction();
    void JoinThreads();
    
    bool mClosed;
    size_t mNumberOfThreads;
    TaskBlockingQueueUPtr mTaskQueue;
    std::vector<std::thread> mThreads;
};
