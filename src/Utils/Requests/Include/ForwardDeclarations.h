#pragma once

#include <memory>

#define REQUESTS_DECLARE_SMART_PTRS(className) \
    class className; \
    using className##Ptr = std::shared_ptr<className>; \
    using className##UPtr = std::unique_ptr<className>; \
    using className##WPtr = std::weak_ptr<className>;

namespace Http {    
    REQUESTS_DECLARE_SMART_PTRS(Requests)
    REQUESTS_DECLARE_SMART_PTRS(RequestsFactory)

    REQUESTS_DECLARE_SMART_PTRS(Request)
    REQUESTS_DECLARE_SMART_PTRS(RequestImpl)
    REQUESTS_DECLARE_SMART_PTRS(GetRequest)
    REQUESTS_DECLARE_SMART_PTRS(PostRequest)
    REQUESTS_DECLARE_SMART_PTRS(PutRequest)
    REQUESTS_DECLARE_SMART_PTRS(DeleteRequest)
    REQUESTS_DECLARE_SMART_PTRS(RequestWithContent)

    REQUESTS_DECLARE_SMART_PTRS(Response)
    REQUESTS_DECLARE_SMART_PTRS(ResponseImpl)

    REQUESTS_DECLARE_SMART_PTRS(ResponseBuilder)
    
    REQUESTS_DECLARE_SMART_PTRS(IncommingTask)
}
