#include "FixedThreadPool.h"

<<<<<<< HEAD
#include "Task.h"
=======
#include "ThreadPool/Task.h"
>>>>>>> nebojsakaran

#include <algorithm>

FixedThreadPool::FixedThreadPool(size_t numberOfThreads, TaskBlockingQueueUPtr blockingQueue)
    : mNumberOfThreads(numberOfThreads)
    , mTaskQueue(std::move(blockingQueue)) {
}

FixedThreadPool::~FixedThreadPool() {
    Close();
    JoinThreads();
}

void FixedThreadPool::Start() {
    try {
        for(unsigned int i = 0; mTaskQueue->IsClosed() == false && i < mNumberOfThreads; i++) {
            mThreads.emplace_back(&FixedThreadPool::WorkerFunction, this);
        }
    } catch (...) {
        Close();
        throw;
    }
}

void FixedThreadPool::Close() {
    if (mTaskQueue) {
        mTaskQueue->Close();   
    }
}

void FixedThreadPool::Enqueue(TaskPtr task) {
    if (mTaskQueue) {
        mTaskQueue->PushBack(task);
    }
}

void FixedThreadPool::Urgent(TaskPtr task) {
    if (mTaskQueue) {
        mTaskQueue->PushFront(task);
    }
}

void FixedThreadPool::WorkerFunction() {
    while(true) {
        TaskPtr task;
        QueueOperationStatus queueOperationStatus = mTaskQueue->PopFront(&task);
        if (queueOperationStatus == QueueOperationStatus::CLOSED) {
            break;
        } else {
            task->Execute();
        }
    }
}

void FixedThreadPool::JoinThreads() {
    std::for_each(mThreads.begin(), mThreads.end(), [](std::thread& t) {
        if (t.joinable()) {
            t.join();
        }
    });
}
