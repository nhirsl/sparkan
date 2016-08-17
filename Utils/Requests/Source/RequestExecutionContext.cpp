#include "RequestExecutionContext.h"

namespace Http {
    RequestExecutionContext::RequestExecutionContext(RequestPtr request)
        : mExecutionStatus(RequestExecutionStatus::PENDING)
        , mResponseBuilder(new ResponseBuilder())
        , mRequest(request) {
    }

    ResponseBuilderPtr RequestExecutionContext::getResponseBuilder() const {
        return mResponseBuilder;
    }

    RequestPtr RequestExecutionContext::getRequest() const {
        return mRequest;
    }
    
    void RequestExecutionContext::setExecutionStatus(RequestExecutionStatus executionStatus) {
        std::lock_guard<std::mutex> lock(mMutex);
        mExecutionStatus = executionStatus;
    }

    RequestExecutionStatus RequestExecutionContext::getExecutionStatus() {
        std::lock_guard<std::mutex> lock(mMutex);
        return mExecutionStatus;
    }

    void RequestExecutionContext::executeIfPending(std::function<void()> ifPendingProc) {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mExecutionStatus == RequestExecutionStatus::PENDING) {
            if (ifPendingProc) {
                ifPendingProc();
            }
        }
    }
}
