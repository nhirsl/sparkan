#pragma once

#include "Requests/ForwardDeclarations.h"
#include "Requests/ProtocolVersion.h"

#include <cstddef>
#include <string>
#include <map>

namespace Http {
    class ResponseBuilder {
    public:
        ResponseBuilder();
        
        ~ResponseBuilder();

        ResponseUPtr Build();
        
        void AddHeader(const std::string& headerKey, const std::string& headerValue);

        void SetProtocolVersion(ProtocolVersion protocolVersion);
        
        void SetStatusCode(unsigned int statusCode);
        
        void SetStatusText(std::string statusText);
        
        bool IsHttpStatusHeaderParsed() const;
        
        void SetHttpStatusHeaderIsParsed(bool httpStatusHeaderParsed);    

        size_t AppendToContent(void* content, size_t contentLength);
        
        void SetRequest(RequestPtr aRequest);
        
    private:
        void InitContentBuffer();
        
        size_t GetContentLength() const;
        
        size_t GetAvailableSizeInContentBuffer();
        
        bool ContentBufferHasEnoughSpaceToAppend(size_t contentLength);
        
        void IncreaseContentBufferFor(size_t increaseSize);

        size_t CopyToContentBuffer(void* content, size_t contentLength);

        bool HeaderExists(const std::string& headerKey);
        
        std::string GetHeaderValue(const std::string& headerKey);
        
        ProtocolVersion mProtocolVersion;
        unsigned int mStatusCode;
        std::string mStatusText;
        
        std::map<std::string, std::string> mHeaders;
        
        char* mContentBuffer;
        char* mCurrentContentPosition;
        size_t mBufferCapacity;
        size_t mBufferIncreaseRate;

        bool mHttpStatusHeaderIsParsed;
        
        RequestPtr mRequest;
    };
}
