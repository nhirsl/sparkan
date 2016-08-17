#pragma once

#include "ForwardDeclarations.h"
#include "MethodEnum.h"

namespace Http {
    class Requests {
    public:
        Requests() = default;
        
        virtual ~Requests() = default;

        static RequestsUPtr CreateInstance();
        
        virtual HandlerUPtr Submit(RequestPtr request, ResponseHandlerType responseHandler) = 0;
        
        virtual HandlerUPtr Urgent(RequestPtr request, ResponseHandlerType responseHandler) = 0;
    };
}
