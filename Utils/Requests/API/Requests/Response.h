#pragma once

#include "ForwardDeclarations.h"

#include "Request.h"

#include <string>
#include <map>

namespace Http {
    class Response {
    public:
        Response() = default;
        
        virtual ~Response() = default;
        
        virtual void* GetContent() = 0;
                
        virtual size_t GetContentLength() = 0;
        
        virtual std::string GetContentType() = 0;
        
        virtual std::map<std::string, std::string> GetHeaders() = 0;
        
        virtual std::string GetHeaderValue(std::string headerKey) = 0;
        
        virtual bool HeaderExists(const std::string& header) = 0;

        virtual ProtocolVersion GetProtocolVersion() = 0;
        
        virtual unsigned int GetStatusCode() = 0;
        
        virtual std::string GetStatusText() = 0;
        
        virtual RequestPtr GetRequest() = 0;
    };
}
