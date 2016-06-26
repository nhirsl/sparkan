#include "FixedThreadPool.h"

#include "WorkerTerminated.h"

FixedThreadPool::FixedThreadPool(size_t numberOfThread)
    : mNumberOfThreads(numberOfThread)
    , mTerminated(false) {
}

FixedThreadPool::~FixedThreadPool() {
    Terminate();
    
    // Join threads from the pool
    for(std::thread& t : mThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void FixedThreadPool::Start() {
    try {
        for(unsigned int i = 0; mTerminated == false && i < mNumberOfThreads; i++) {
            mThreads.push_back(std::thread(&FixedThreadPool::WorkerFunction, this));
        }
    } catch (...) {
        Terminate();
        throw;
    }
}

void FixedThreadPool::Terminate() {
    std::lock_guard<std::mutex> lock(mMutex);
    mTerminated = true;
    
    // Wake up all threads waiting on mQueueIsNotEmpty
    mQueueIsNotEmpty.notify_all();
}

void FixedThreadPool::Enqueue(Task task) {
    PushBack(std::move(task));
}

void FixedThreadPool::Urgent(Task task) {
    PushFront(std::move(task));
}

void FixedThreadPool::WorkerFunction() {
    try {
        while(true) {
            Task task = GetNext();
            task();
        }
    } catch (WorkerTerminated& workerTerminated) {
    }
}

void FixedThreadPool::PushBack(Task task) {
    std::lock_guard<std::mutex> lock(mMutex);
    if(mTerminated == false) {
        mQueue.push_back(std::move(task));
        mQueueIsNotEmpty.notify_all();
    }
}

void FixedThreadPool::PushFront(Task task) {
    std::lock_guard<std::mutex> lock(mMutex);
    if(mTerminated == false) {
        mQueue.push_front(std::move(task));
        mQueueIsNotEmpty.notify_all();
    }
}

Task FixedThreadPool::GetNext() {
    std::unique_lock<std::mutex> lock(mMutex);
    while(mTerminated == false && mQueue.size() == 0) {
        mQueueIsNotEmpty.wait(lock);
    }
    if (mTerminated) {
        throw WorkerTerminated();
    }
    std::function<void()> nextTask = mQueue.front();
    mQueue.pop_front();
    return std::move(nextTask);
}
