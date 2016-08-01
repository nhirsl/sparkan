#include "NonblockingRecursiveLock.h"

NonblockingRecursiveLock::NonblockingRecursiveLock(std::recursive_mutex& m)
    : mMutex(m) {
}

NonblockingRecursiveLock::~NonblockingRecursiveLock() {
    mMutex.unlock();
}

bool NonblockingRecursiveLock::TryLock() {
    return mMutex.try_lock();
}
