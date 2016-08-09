#pragma once

<<<<<<< HEAD
#include "ForwardDeclarations.h"

#include <cstddef>
#include <string>
#include <unordered_map>
=======
#include "Requests/ForwardDeclarations.h"
#include "Requests/ProtocolVersion.h"

#include <cstddef>
#include <string>
#include <map>
>>>>>>> nebojsakaran

namespace Http {
    class ResponseBuilder {
    public:
        ResponseBuilder();
        
        ~ResponseBuilder();

        ResponseUPtr Build();
        
        void AddHeader(const std::string& headerKey, const std::string& headerValue);

<<<<<<< HEAD
        void SetHttpVersion(std::string httpVersion);
=======
        void SetProtocolVersion(ProtocolVersion protocolVersion);
>>>>>>> nebojsakaran
        
        void SetStatusCode(unsigned int statusCode);
        
        void SetStatusText(std::string statusText);
        
        bool IsHttpStatusHeaderParsed() const;
        
        void SetHttpStatusHeaderIsParsed(bool httpStatusHeaderParsed);    

        size_t AppendToContent(void* content, size_t contentLength);
        
        void SetRequest(RequestUPtr aRequest);
        
    private:
        void InitContentBuffer();
        
        size_t GetContentLength() const;
        
        size_t GetAvailableSizeInContentBuffer();
        
        bool ContentBufferHasEnoughSpaceToAppend(size_t contentLength);
        
        void IncreaseContentBufferFor(size_t increaseSize);

        size_t CopyToContentBuffer(void* content, size_t contentLength);

        bool HeaderExists(const std::string& headerKey);
        
        std::string GetHeaderValue(const std::string& headerKey);
        
<<<<<<< HEAD
        std::string mHttpVersion;
        unsigned int mStatusCode;
        std::string mStatusText;
        
        std::unordered_map<std::string, std::string> mHeaders;
=======
        ProtocolVersion mProtocolVersion;
        unsigned int mStatusCode;
        std::string mStatusText;
        
        std::map<std::string, std::string> mHeaders;
>>>>>>> nebojsakaran
        
        char* mContentBuffer;
        char* mCurrentContentPosition;
        size_t mBufferCapacity;
        size_t mBufferIncreaseRate;

        bool mHttpStatusHeaderIsParsed;
        
        RequestUPtr mRequest;
    };
}
