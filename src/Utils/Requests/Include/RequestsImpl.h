#pragma once

#include "Requests.h"

#include "ThreadPool.h"

namespace Http {
    class RequestsImpl : public Requests {
    public:
        RequestsImpl();
        
        virtual ~RequestsImpl();

        virtual void Get(const std::string& url,
                         std::unordered_map<std::string, std::string> headers, 
                         std::function<void(ResponseUPtr)> responseHandler) override;

        virtual void Get(const std::string& url,
                         std::unordered_map<std::string, std::string> queryStringParams,
                         std::unordered_map<std::string, std::string> headers,
                         std::function<void(ResponseUPtr)> responseHandler) override;
        
        virtual void Get(const std::string& url, 
                         std::function<void(ResponseUPtr)> responseHandler) override;

        virtual void Post(const std::string& url, 
                          const std::string& content,
                          std::unordered_map<std::string, std::string> headers, 
                          std::function<void(ResponseUPtr)> responseHandler) override;

        virtual void Post(const std::string& url, 
                          const std::string& content,
                          std::function<void(ResponseUPtr)> responseHandler) override;                         
                         
        virtual void Delete(const std::string& url, 
                            std::unordered_map<std::string, std::string> headers, 
                            std::function<void(ResponseUPtr)> responseHandler) override;

        virtual void Delete(const std::string& url, 
                            std::function<void(ResponseUPtr)> responseHandler) override;
                            
    private:
        std::string AddQueryStringToUrl(const std::string& url, std::unordered_map<std::string, std::string> queryStringParams);
        
        ThreadPoolUPtr mIncommingTasks;
    };
}
