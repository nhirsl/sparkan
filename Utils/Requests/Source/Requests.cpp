<<<<<<< HEAD
#include "Requests.h"
=======
#include "Requests/Requests.h"
>>>>>>> nebojsakaran

#include "RequestsImpl.h"

namespace Http {
<<<<<<< HEAD
    std::mutex Requests::mutex;
    
    bool Requests::destroyed = false;
    
    RequestsPtr Requests::requests;
    
    RequestsPtr Requests::GetInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (destroyed) {
            return nullptr;
        } else {
            if (requests == nullptr) {
                requests.reset(new RequestsImpl());
            }
            return requests;
        }
    }
    
    void Requests::Destroy() {
        std::lock_guard<std::mutex> lock(mutex);
        requests.reset();
        destroyed = true;
=======
    RequestsUPtr Requests::CreateInstance() {
        RequestsImplUPtr requestsImpl(new RequestsImpl());
        return std::move(requestsImpl);
>>>>>>> nebojsakaran
    }
}
