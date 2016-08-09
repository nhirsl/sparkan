#pragma once

#include "ForwardDeclarations.h"
#include "MethodEnum.h"

namespace Http {
    class Requests {
    public:
        Requests() = default;
        
        virtual ~Requests() = default;

        static RequestsUPtr CreateInstance();
        
        virtual void Submit(RequestUPtr request, ResponseHandlerType responseHandler) = 0;
        
        virtual void Urgent(RequestUPtr request, ResponseHandlerType responseHandler) = 0;
    };
}
