#pragma once

#include "Requests/ForwardDeclarations.h"

#include "Requests/ProtocolVersion.h"
#include "Requests/Request.h"

#include <string>
#include <map>

namespace Http {
    class RequestImpl : public Request {
    public:
        RequestImpl();
        
        virtual ~RequestImpl();
        
        virtual Method GetMethod() override;
        
        virtual std::string GetUrl() override;
        
        virtual ProtocolVersion GetProtocolVersion() override;
        
        virtual std::string GetHeaderValue(std::string headerKey) override;
        
        virtual std::map<std::string, std::string> GetHeaders() override;
        
        virtual bool HeaderExists(const std::string& headerKey) override;
        
        virtual void* GetContent() override;
        
        virtual size_t GetContentLength() override;
        
        void SetMethod(Method method);
        
        void SetUrl(const std::string& url);
        
        void SetProtocolVersion(ProtocolVersion httpVersion);
        
        void SetHeaders(std::map<std::string, std::string> headers);
        
        void SetContent(void* content, size_t contentLength);
        
    private:
        Method mMethod;

        std::string mUrl;
        
        ProtocolVersion mProtocolVersion;
        
        std::map<std::string, std::string> mHeaders;
        
        void* mContent;
        size_t mContentLength;
    };
}
