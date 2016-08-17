#pragma once

#include "Requests/ForwardDeclarations.h"
#include "Requests/Handler.h"

#include "RequestExecutionContext.h"

namespace Http {
    class HandlerImpl : public Handler {
    public:
        HandlerImpl(RequestExecutionContextPtr requestExecutionContext);

        virtual ~HandlerImpl() = default;

        virtual void terminate() override;
        
        virtual void ifPending(std::function<void()> ifPendingProc) override;

    private:
        RequestExecutionContextPtr mRequestExecutionContext;
    };
}
