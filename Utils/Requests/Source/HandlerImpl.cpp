#include "HandlerImpl.h"

#include "RequestExecutionContext.h"

namespace Http {
    HandlerImpl::HandlerImpl(RequestExecutionContextPtr requestExecutionContext)
        : mRequestExecutionContext(requestExecutionContext) {
    }
    
    void HandlerImpl::terminate() {
        mRequestExecutionContext->setExecutionStatus(RequestExecutionStatus::TERMINATED);
    }

    void HandlerImpl::ifPending(std::function<void()> ifPendingProc) {
        mRequestExecutionContext->executeIfPending(ifPendingProc);
    }
}
