#pragma once

#include "ForwardDeclarations.h"
#include "ProtocolVersion.h"
#include "MethodEnum.h"

#include <string>
#include <cstddef>

namespace Http {
    class RequestBuilder {
    public:
        RequestBuilder() = default;
        
        virtual ~RequestBuilder() = default;
        
        static RequestBuilderUPtr CreateInstance();

        virtual void SetMethod(Method method) = 0;
        
        virtual void SetUrl(std::string url) = 0;
        
        virtual void SetProtocolVersion(ProtocolVersion protocolVersion) = 0;
        
        virtual void SetHeader(std::string headerName, std::string headerValue) = 0;
        
        virtual void SetContent(void* content, size_t contentLength) = 0;
        
        virtual void setFollowLocation(bool followLocation) = 0;
        
        virtual RequestBuilderUPtr Copy() = 0;
        
        virtual RequestPtr Build() = 0;
    };
}
