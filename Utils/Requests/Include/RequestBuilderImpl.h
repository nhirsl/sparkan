#pragma once

#include "Requests/RequestBuilder.h"

#include <map>

namespace Http {
    class RequestBuilderImpl : public RequestBuilder {
    public:
        RequestBuilderImpl();
        
        virtual ~RequestBuilderImpl();

        virtual void SetMethod(Method method) override;
        
        virtual void SetUrl(std::string url) override;
        
        virtual void SetProtocolVersion(ProtocolVersion protocolVersion) override;
        
        virtual void SetHeader(std::string headerName, std::string headerValue) override;
        
        virtual void SetContent(void* content, size_t contentLength) override;
        
        virtual void setFollowLocation(bool followLocation) override;
        
        virtual RequestBuilderUPtr Copy() override;
        
        virtual RequestPtr Build() override;
        
    private:
        void SetHeaders(
            std::map<std::string, std::string>::iterator begin, 
            std::map<std::string, std::string>::iterator end);
        
        Method mMethod;
        
        std::string mUrl;
        
        ProtocolVersion mProtocolVersion;
        
        std::map<std::string, std::string> mHeaders;
        
        void* mContent;
        size_t mContentLength;
        
        bool mFollowLocation;
    };
}
