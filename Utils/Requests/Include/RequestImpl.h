#pragma once

<<<<<<< HEAD
#include "ForwardDeclarations.h"

#include "Request.h"

//#include "ThreadpOOl"
//#include "ThreadPool.h"

#include <string>
#include <unordered_map>
#include <functional>
=======
#include "Requests/ForwardDeclarations.h"

#include "Requests/ProtocolVersion.h"
#include "Requests/Request.h"

#include <string>
#include <map>
>>>>>>> nebojsakaran

namespace Http {
    class RequestImpl : public Request {
    public:
        RequestImpl();
        
        virtual ~RequestImpl();
        
<<<<<<< HEAD
        virtual std::string GetUrl() override;
        
        virtual std::string GetHttpVersion() override;
        
        virtual std::string GetHeaderValue(std::string headerKey) override;
        
        virtual std::unordered_map<std::string, std::string> GetHeaders() override;
=======
        virtual Method GetMethod() override;
        
        virtual std::string GetUrl() override;
        
        virtual ProtocolVersion GetProtocolVersion() override;
        
        virtual std::string GetHeaderValue(std::string headerKey) override;
        
        virtual std::map<std::string, std::string> GetHeaders() override;
>>>>>>> nebojsakaran
        
        virtual bool HeaderExists(const std::string& headerKey) override;
        
        virtual void* GetContent() override;
        
        virtual size_t GetContentLength() override;
        
<<<<<<< HEAD
        void SetUrl(const std::string& url);
        
        void AddHeaders(std::unordered_map<std::string, std::string> headers);
        
        void OnResponse(std::function<void(ResponseUPtr)> fn);
        
        std::function<void(ResponseUPtr)> GetResponseHandler();
        
    private:
        std::function<void(ResponseUPtr)> mResponseHandler;
        
        std::string mUrl;
        
        std::unordered_map<std::string, std::string> mHeaders;
=======
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
>>>>>>> nebojsakaran
    };
}
