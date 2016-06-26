#pragma once

#include "ForwardDeclarations.h"

namespace Http {
    class RequestPerformer final {
    public:
        RequestPerformer() = delete;
        
        static void Init();
        
        static void Perform(RequestImplUPtr requestImpl);
    };
}
