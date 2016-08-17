#pragma once

#include "Requests/ForwardDeclarations.h"

#include "RequestExecutionStatus.h"
#include "ResponseBuilder.h"

#include <mutex>

namespace Http {
    class RequestExecutionContext final {
    public:
        RequestExecutionContext(RequestPtr mRequest);

        ~RequestExecutionContext() = default;

        ResponseBuilderPtr getResponseBuilder() const;

        RequestPtr getRequest() const;
        
        void setExecutionStatus(RequestExecutionStatus executionStatus);
        
        RequestExecutionStatus getExecutionStatus();

        void executeIfPending(std::function<void()> ifPendingProc);

    private:
        RequestExecutionStatus mExecutionStatus;
        
        ResponseBuilderPtr mResponseBuilder;

        RequestPtr mRequest;
        
        std::mutex mMutex;
    };
}
