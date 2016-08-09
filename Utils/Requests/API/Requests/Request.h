#pragma once

#include <map>
#include <string>

#include "ProtocolVersion.h"
#include "MethodEnum.h"

namespace Http {
    class Request {
    public:
        Request() = default;
        
        virtual ~Request() = default;
        
        virtual Method GetMethod() = 0;
        
        virtual std::string GetUrl() = 0;
        
        virtual ProtocolVersion GetProtocolVersion() = 0;
        
        virtual std::map<std::string, std::string> GetHeaders() = 0;
        
        virtual std::string GetHeaderValue(std::string headerKey) = 0;
        
        virtual bool HeaderExists(const std::string& header) = 0;
        
        virtual void* GetContent() = 0;
        
        virtual size_t GetContentLength() = 0;
    };
}
