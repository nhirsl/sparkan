#pragma once

#include "Response.h"

namespace Http {
    class ResponseImpl : public Response {
    public:
        ResponseImpl();
        
        virtual ~ResponseImpl();
        
        virtual void* GetContent() override; 
        
        virtual size_t GetContentLength() override;
        
        virtual std::string GetContentType() override;
        
        virtual std::string GetHeaderValue(std::string headerKey) override;
        
        virtual std::unordered_map<std::string, std::string> GetHeaders() override;
        
        virtual bool HeaderExists(const std::string& headerKey) override;
        
        virtual std::string GetHttpVersion() override;
        
        virtual unsigned int GetStatusCode() override;
        
        virtual std::string GetStatusText() override;
        
        virtual RequestUPtr GetRequest() override;
        
        void SetHttpVersion(const std::string& httpVersion);
        
        void SetStatusCode(unsigned int statusCode);
        
        void SetStatusText(const std::string& statusText);
        
        void SetHeaders(std::unordered_map<std::string, std::string> headers);
        
        void SetContent(void* content, size_t contentLength);
        
        void SetRequest(RequestUPtr aRequest);
        
    private:
        RequestUPtr mRequest;
        
        std::string mHttpVersion;
        unsigned int mStatusCode;
        std::string mStatusText;
        
        void* mContent;
        size_t mContentLength;
        
        std::unordered_map<std::string, std::string> mHeaders;
    };
}
