#pragma once

#include "ForwardDeclarations.h"

#include <mutex>

namespace Http {
    class RequestsFactory {
    public:
        ~RequestsFactory() = default;
        
        static RequestsFactoryPtr GetInstance();
        
        RequestsUPtr CreateInstance();
        
    private:
        RequestsFactory() = default;
        
        static std::mutex mutex;
        
        static RequestsFactoryWPtr instance;
    };
}
