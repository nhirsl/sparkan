#include "Requests/Requests.h"

#include "RequestsImpl.h"

namespace Http {
    RequestsUPtr Requests::CreateInstance() {
        RequestsImplUPtr requestsImpl(new RequestsImpl());
        return std::move(requestsImpl);
    }
}
