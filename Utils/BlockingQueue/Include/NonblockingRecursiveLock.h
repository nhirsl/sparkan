#pragma once

#include <mutex>

class NonblockingRecursiveLock final {
public:
    NonblockingRecursiveLock(std::recursive_mutex& m);
    
    ~NonblockingRecursiveLock();
    
    bool TryLock();
    
private:
    std::recursive_mutex& mMutex;
};
