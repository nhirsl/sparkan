#pragma once
    
#include "RequestWithContent.h"

namespace Http {
    class PostRequest : public RequestWithContent {
    public:
        PostRequest() = default;
        virtual ~PostRequest() = default;
        
        virtual Method GetMethod() override;
    };
}
