#pragma once

#include "ForwardDeclarations.h"

#include "Request.h"

//#include "ThreadpOOl"
//#include "ThreadPool.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace Http {
    class RequestImpl : public Request {
    public:
        RequestImpl();
        
        virtual ~RequestImpl();
        
        virtual std::string GetUrl() override;
        
        virtual std::string GetHttpVersion() override;
        
        virtual std::string GetHeaderValue(std::string headerKey) override;
        
        virtual std::unordered_map<std::string, std::string> GetHeaders() override;
        
        virtual bool HeaderExists(const std::string& headerKey) override;
        
        virtual void* GetContent() override;
        
        virtual size_t GetContentLength() override;
        
        void SetUrl(const std::string& url);
        
        void AddHeaders(std::unordered_map<std::string, std::string> headers);
        
        void OnResponse(std::function<void(ResponseUPtr)> fn);
        
        std::function<void(ResponseUPtr)> GetResponseHandler();
        
    private:
        std::function<void(ResponseUPtr)> mResponseHandler;
        
        std::string mUrl;
        
        std::unordered_map<std::string, std::string> mHeaders;
    };
}
