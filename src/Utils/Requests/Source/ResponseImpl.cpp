#include "ResponseImpl.h"

#include "StringUtils.h"

#include <iostream>
#include <string>

namespace Http {
    ResponseImpl::ResponseImpl() 
        : mContent(0)
        , mContentLength(0) {
    }

    ResponseImpl::~ResponseImpl() {
        mContent = 0;
    }

    void* ResponseImpl::GetContent() {
        return mContent;
    }

    size_t ResponseImpl::GetContentLength() {
        std::string contentLength = GetHeaderValue("Content-Length");
        if(!contentLength.empty()) {
            return StringUtils::ToUnsignedInt(contentLength);
        }
        return 0;
    }

    std::string ResponseImpl::GetContentType() {
        return GetHeaderValue("Content-Type");
    }

    std::string ResponseImpl::GetHeaderValue(std::string headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        if(iter != mHeaders.end()) {
            return iter->second;
        }
        return "";
    }

    std::unordered_map<std::string, std::string> ResponseImpl::GetHeaders() {
        return mHeaders;
    }

    std::string ResponseImpl::GetHttpVersion() {
        return mHttpVersion;
    }

    unsigned int ResponseImpl::GetStatusCode() {
        return mStatusCode;
    }

    std::string ResponseImpl::GetStatusText() {
        return mStatusText;
    }

    bool ResponseImpl::HeaderExists(const std::string& headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        return iter != mHeaders.end();
    }

    RequestUPtr ResponseImpl::GetRequest() {
        return std::move(mRequest);
    }
    
    void ResponseImpl::SetHeaders(std::unordered_map<std::string, std::string> headers) {
        mHeaders = headers;
    }

    void ResponseImpl::SetContent(void* content, size_t contentLength) {
        mContent = content;
        mContentLength = contentLength;
    }

    void ResponseImpl::SetHttpVersion(const std::string& httpVersion) {
        mHttpVersion = httpVersion;
    }

    void ResponseImpl::SetStatusCode(unsigned int statusCode){
        mStatusCode = statusCode;
    }

    void ResponseImpl::SetStatusText(const std::string& statusText) {
        mStatusText = statusText;
    }
    
    void ResponseImpl::SetRequest(RequestUPtr aRequest) {
        mRequest = std::move(aRequest);
    }
}
