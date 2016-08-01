#pragma once

#include "RequestImpl.h"

namespace Http {
    class GetRequest : public RequestImpl {
    public:
        GetRequest() = default;
        virtual ~GetRequest() = default;
        
        virtual Method GetMethod() override;
    };
}
