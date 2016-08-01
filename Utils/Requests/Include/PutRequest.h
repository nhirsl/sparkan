#pragma once

#include "RequestWithContent.h"

namespace Http {
    class PutRequest : public RequestWithContent {
    public:
        PutRequest() = default;
        virtual ~PutRequest() = default;
        
        virtual Method GetMethod() override;
    };
}
