#include "Requests/RequestBuilder.h"

#include "RequestBuilderImpl.h"

namespace Http {
    RequestBuilderUPtr RequestBuilder::Create() {
        return RequestBuilderUPtr(new RequestBuilderImpl());
    }
}
