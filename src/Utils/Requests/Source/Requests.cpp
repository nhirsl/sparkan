#include "Requests.h"

#include "RequestsImpl.h"

namespace Http {
    std::mutex Requests::mutex;
    
    RequestsPtr Requests::requests;
    
    RequestsPtr Requests::GetInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (requests == nullptr) {
            requests.reset(new RequestsImpl());
        }
        return requests;
    }
}
