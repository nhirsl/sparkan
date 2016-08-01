#pragma once

#include "ForwardDeclarations.h"

#include "Request.h"

#include <string>
#include <unordered_map>

namespace Http {
    class Response {
    public:
        Response() = default;
        
        virtual ~Response() = default;
        
        virtual void* GetContent() = 0;
                
        virtual size_t GetContentLength() = 0;
        
        virtual std::string GetContentType() = 0;
        
        virtual std::unordered_map<std::string, std::string> GetHeaders() = 0;
        
        virtual std::string GetHeaderValue(std::string headerKey) = 0;
        
        virtual bool HeaderExists(const std::string& header) = 0;

        virtual std::string GetHttpVersion() = 0;
        
        virtual unsigned int GetStatusCode() = 0;
        
        virtual std::string GetStatusText() = 0;
        
        virtual RequestUPtr GetRequest() = 0;
    };
}
