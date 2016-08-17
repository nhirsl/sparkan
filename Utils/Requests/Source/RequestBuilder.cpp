#include "Requests/RequestBuilder.h"

#include "RequestBuilderImpl.h"

namespace Http {
    RequestBuilderUPtr RequestBuilder::CreateInstance() {
        return RequestBuilderUPtr(new RequestBuilderImpl());
    }
}
