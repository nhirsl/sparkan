#pragma once

#include "ForwardDeclarations.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace Http {
    class Requests {
    public:
        Requests() = default;
        
        virtual ~Requests() = default;

        static RequestsPtr GetInstance();
        
        virtual void Get(const std::string& url,
                         std::unordered_map<std::string, std::string> queryStringParams,
                         std::unordered_map<std::string, std::string> headers,
                         std::function<void(ResponseUPtr)> responseHandler) = 0;
    
        virtual void Get(const std::string& url,
                         std::unordered_map<std::string, std::string> headers, 
                         std::function<void(ResponseUPtr)> responseHandler) = 0;

        virtual void Get(const std::string& url, 
                         std::function<void(ResponseUPtr)> responseHandler) = 0;

        virtual void Post(const std::string& url, 
                          const std::string& content,
                          std::unordered_map<std::string, std::string> headers, 
                          std::function<void(ResponseUPtr)> responseHandler) = 0;

        virtual void Post(const std::string& url, 
                          const std::string& content,
                          std::function<void(ResponseUPtr)> responseHandler) = 0;
        
        virtual void Delete(const std::string& url, 
                            std::unordered_map<std::string, std::string> headers, 
                            std::function<void(ResponseUPtr)> responseHandler) = 0;

        virtual void Delete(const std::string& url, 
                            std::function<void(ResponseUPtr)> responseHandler) = 0;
                         
    };
}
