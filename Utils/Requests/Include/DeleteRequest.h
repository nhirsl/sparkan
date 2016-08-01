#pragma once

#include "RequestImpl.h"

namespace Http {
    class DeleteRequest : public RequestImpl {
    public:
        DeleteRequest() = default;
        virtual ~DeleteRequest() = default;
        
        virtual Method GetMethod() override;
    };
}
