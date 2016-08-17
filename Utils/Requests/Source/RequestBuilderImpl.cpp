#include "RequestBuilderImpl.h"

#include "RequestImpl.h"

#include <cstring>

namespace Http {
    RequestBuilderImpl::RequestBuilderImpl() 
        : mMethod(Method::GET)
        , mProtocolVersion(ProtocolVersion::HTTP_1_1)
        , mContent(0)
        , mContentLength(0)
        , mFollowLocation(true) {
    }
    
    RequestBuilderImpl::~RequestBuilderImpl() {
        delete[] static_cast<char*>(mContent);
        mContent = nullptr;
    }
    
    void RequestBuilderImpl::SetMethod(Method method) {
        mMethod = method;
    }
    
    void RequestBuilderImpl::SetUrl(std::string url) {
        mUrl = std::move(url);
    }
    
    void RequestBuilderImpl::SetProtocolVersion(ProtocolVersion protocolVersion) {
        mProtocolVersion = protocolVersion;
    }
    
    void RequestBuilderImpl::SetHeader(std::string headerName, std::string headerValue) {
        mHeaders[headerName] = headerValue;
    }
    
    void RequestBuilderImpl::SetContent(void* content, size_t contentLength) {
        mContent = new char[contentLength];
        memcpy(mContent, content, contentLength);
        mContentLength = contentLength;
    }
    
    RequestBuilderUPtr RequestBuilderImpl::Copy() {
        RequestBuilderImplUPtr requestBuilderImpl(new RequestBuilderImpl());
        requestBuilderImpl->SetMethod(mMethod);
        requestBuilderImpl->SetUrl(mUrl);
        requestBuilderImpl->SetProtocolVersion(mProtocolVersion);
        requestBuilderImpl->SetHeaders(mHeaders.begin(), mHeaders.end());
        requestBuilderImpl->SetContent(mContent, mContentLength);
        requestBuilderImpl->setFollowLocation(mFollowLocation);
        return std::move(requestBuilderImpl);
    }
    
    RequestPtr RequestBuilderImpl::Build() {
        RequestImplPtr requestImpl(new RequestImpl());
        requestImpl->SetMethod(mMethod);
        requestImpl->SetUrl(mUrl);
        requestImpl->SetProtocolVersion(mProtocolVersion);
        requestImpl->SetHeaders(mHeaders);
        requestImpl->SetContent(mContent, mContentLength);
        requestImpl->setFollowLocation(mFollowLocation);
        return requestImpl;
    }
    
    void RequestBuilderImpl::SetHeaders(
        std::map<std::string, std::string>::iterator begin, 
        std::map<std::string, std::string>::iterator end) {
        mHeaders.insert(begin, end);
    }
    
    void RequestBuilderImpl::setFollowLocation(bool followLocation) {
        mFollowLocation = followLocation;
    }
}
