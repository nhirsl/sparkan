#include "RequestImpl.h"

#include "ResponseBuilder.h"
#include "CurlDeliveredDataHandler.h"

#include <string>
#include <cstring>
#include <map>

namespace Http {
    RequestImpl::RequestImpl()
        : mContent(0)
        , mContentLength(0) {
    }
    
    RequestImpl::~RequestImpl() {
        delete[] static_cast<char*>(mContent);
        mContent = 0;
    }
    
    Method RequestImpl::GetMethod() {
        return mMethod;
    }
    
    std::string RequestImpl::GetUrl() {
        return mUrl;
    }
    
    ProtocolVersion RequestImpl::GetProtocolVersion() {
        return mProtocolVersion;
    }
    
    std::string RequestImpl::GetHeaderValue(std::string headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        if(iter != mHeaders.end()) {
            return iter->second;
        }
        return "";
    }    
    
    std::map<std::string, std::string> RequestImpl::GetHeaders() {
        return mHeaders;
    }
    
    bool RequestImpl::HeaderExists(const std::string& headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        return iter != mHeaders.end();
    }    
    
    void* RequestImpl::GetContent() {
        return mContent;
    }
    
    size_t RequestImpl::GetContentLength() {
        return mContentLength;
    }
    
    void RequestImpl::SetMethod(Method method) {
        mMethod = method;
    }
    
    void RequestImpl::SetUrl(const std::string& url) {
        mUrl = url;
    }
    
    void RequestImpl::SetProtocolVersion(ProtocolVersion protocolVersion) {
        mProtocolVersion = protocolVersion;
    }
    
    void RequestImpl::SetHeaders(std::map<std::string, std::string> headers) {
        mHeaders.insert(headers.begin(), headers.end());
    }

    void RequestImpl::SetContent(void* content, size_t contentLength) {
        mContent = new char[contentLength];
        memcpy(mContent, content, contentLength);
        
        mContentLength = contentLength;
    }
}
