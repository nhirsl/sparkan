#pragma once

#include <memory>

#define DECLARE_SMART_PTRS(className) \
    class className; \
    using className##Ptr = std::shared_ptr<className>; \
    using className##UPtr = std::unique_ptr<className>; \
    using className##WPtr = std::weak_ptr<className>;

namespace Http {    
    DECLARE_SMART_PTRS(Requests)

    DECLARE_SMART_PTRS(Request)
    DECLARE_SMART_PTRS(RequestImpl)
    DECLARE_SMART_PTRS(GetRequest)
    DECLARE_SMART_PTRS(PostRequest)
    DECLARE_SMART_PTRS(PutRequest)
    DECLARE_SMART_PTRS(DeleteRequest)
    DECLARE_SMART_PTRS(RequestWithContent)

    DECLARE_SMART_PTRS(Response)
    DECLARE_SMART_PTRS(ResponseImpl)

    DECLARE_SMART_PTRS(ResponseBuilder)
}
