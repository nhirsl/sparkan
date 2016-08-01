#include "RequestImpl.h"

#include "ResponseBuilder.h"
#include "CurlDeliveredDataHandler.h"

#include <string>
#include <unordered_map>

namespace Http {
    RequestImpl::RequestImpl() {
    }
    
    RequestImpl::~RequestImpl() { 
    }
    
    std::string RequestImpl::GetUrl() {
        return mUrl;
    }
    
    std::string RequestImpl::GetHttpVersion() {
        return "HTTP/1.1";
    }
    
    std::string RequestImpl::GetHeaderValue(std::string headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        if(iter != mHeaders.end()) {
            return iter->second;
        }
        return "";
    }    
    
    std::unordered_map<std::string, std::string> RequestImpl::GetHeaders() {
        return mHeaders;
    }
    
    bool RequestImpl::HeaderExists(const std::string& headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        return iter != mHeaders.end();
    }    
    
    void RequestImpl::SetUrl(const std::string& url) {
        mUrl = url;
    }
    
    void* RequestImpl::GetContent() {
        return 0;
    }
    
    size_t RequestImpl::GetContentLength() {
        return 0;
    }
    
    void RequestImpl::AddHeaders(std::unordered_map<std::string, std::string> headers) {
        mHeaders.insert(headers.begin(), headers.end());
    }
    
    void RequestImpl::OnResponse(std::function<void(ResponseUPtr)> aResponseHandler) {
        mResponseHandler = aResponseHandler;
    }
    
    std::function<void(ResponseUPtr)> RequestImpl::GetResponseHandler() {
        return mResponseHandler;
    }
}
