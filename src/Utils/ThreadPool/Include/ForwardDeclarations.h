#pragma once

#include <memory>
#include <functional>

#define DECLARE_SMART_PTRS(className) \
    class className; \
    using className##Ptr = std::shared_ptr<className>; \
    using className##WPtr = std::weak_ptr<className>; \
    using className##UPtr = std::unique_ptr<className>;
   
DECLARE_SMART_PTRS(ThreadPool);
DECLARE_SMART_PTRS(FixedThreadPool);
DECLARE_SMART_PTRS(ThreadPoolFactory);

using Task = std::function<void()>;
