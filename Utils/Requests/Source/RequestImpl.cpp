#include "RequestImpl.h"

#include "ResponseBuilder.h"
#include "CurlDeliveredDataHandler.h"

#include <string>
<<<<<<< HEAD
#include <unordered_map>

namespace Http {
    RequestImpl::RequestImpl() {
    }
    
    RequestImpl::~RequestImpl() { 
=======
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
>>>>>>> nebojsakaran
    }
    
    std::string RequestImpl::GetUrl() {
        return mUrl;
    }
    
<<<<<<< HEAD
    std::string RequestImpl::GetHttpVersion() {
        return "HTTP/1.1";
=======
    ProtocolVersion RequestImpl::GetProtocolVersion() {
        return mProtocolVersion;
>>>>>>> nebojsakaran
    }
    
    std::string RequestImpl::GetHeaderValue(std::string headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        if(iter != mHeaders.end()) {
            return iter->second;
        }
        return "";
    }    
    
<<<<<<< HEAD
    std::unordered_map<std::string, std::string> RequestImpl::GetHeaders() {
=======
    std::map<std::string, std::string> RequestImpl::GetHeaders() {
>>>>>>> nebojsakaran
        return mHeaders;
    }
    
    bool RequestImpl::HeaderExists(const std::string& headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        return iter != mHeaders.end();
    }    
    
<<<<<<< HEAD
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
=======
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
>>>>>>> nebojsakaran
    }
}
