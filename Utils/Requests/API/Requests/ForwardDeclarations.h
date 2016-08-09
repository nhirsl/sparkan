#pragma once

#include <memory>
#include <functional>

#define REQUESTS_DECLARE_SMART_PTRS(className) \
    class className; \
    using className##Ptr = std::shared_ptr<className>; \
    using className##UPtr = std::unique_ptr<className>; \
    using className##WPtr = std::weak_ptr<className>;

namespace Http {
    REQUESTS_DECLARE_SMART_PTRS(Requests)
    REQUESTS_DECLARE_SMART_PTRS(RequestsImpl)

    REQUESTS_DECLARE_SMART_PTRS(Request)
    REQUESTS_DECLARE_SMART_PTRS(RequestImpl)

    REQUESTS_DECLARE_SMART_PTRS(RequestBuilder)
    REQUESTS_DECLARE_SMART_PTRS(RequestBuilderImpl)
    
    REQUESTS_DECLARE_SMART_PTRS(Response)
    REQUESTS_DECLARE_SMART_PTRS(ResponseImpl)

    REQUESTS_DECLARE_SMART_PTRS(ResponseBuilder)
    
    REQUESTS_DECLARE_SMART_PTRS(IncommingTask)
    
    using ResponseHandlerType = std::function<void(ResponseUPtr)>;
}
