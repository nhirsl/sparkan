#include "RequestsFactory.h"

#include "RequestsImpl.h"

namespace Http {
    std::mutex RequestsFactory::mutex;
    
    RequestsFactoryWPtr RequestsFactory::instance;
    
    RequestsFactoryPtr RequestsFactory::GetInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        RequestsFactoryPtr requestsFactory = instance.lock();
        if (requestsFactory == nullptr) {
            requestsFactory.reset(new RequestsFactory());
            instance = requestsFactory;
        }
        return requestsFactory;
    }
    
    RequestsUPtr RequestsFactory::CreateInstance() {
        return RequestsUPtr(new RequestsImpl());
    }
}
