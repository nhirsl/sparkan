#include "ResponseBuilder.h"

#include "StringUtils.h"
#include "Request.h"
#include "ResponseImpl.h"

#include <iostream>
#include <string>
#include <cmath>

namespace Http {
    ResponseBuilder::ResponseBuilder() 
        : mHttpStatusHeaderIsParsed(false)
        , mContentBuffer(0)
        , mCurrentContentPosition(0)
        , mBufferCapacity(0)
        , mBufferIncreaseRate(512) {
    }

    ResponseBuilder::~ResponseBuilder() {
    }

    ResponseUPtr ResponseBuilder::Build() {
        ResponseImplUPtr aResponseImpl(new ResponseImpl());
        aResponseImpl->SetRequest(std::move(mRequest));
        aResponseImpl->SetHttpVersion(mHttpVersion);
        aResponseImpl->SetStatusCode(mStatusCode);
        aResponseImpl->SetStatusText(mStatusText);
        aResponseImpl->SetHeaders(mHeaders);
        aResponseImpl->SetContent(mContentBuffer, GetContentLength());
        return std::move(aResponseImpl);
    }

    void ResponseBuilder::AddHeader(const std::string& headerKey, const std::string& headerValue) {
        mHeaders[headerKey] = headerValue;
    }

    void ResponseBuilder::SetHttpVersion(std::string httpVersion) {
        mHttpVersion = httpVersion;
    }

    void ResponseBuilder::SetStatusCode(unsigned int statusCode) {
        mStatusCode = statusCode;
    }

    void ResponseBuilder::SetStatusText(std::string statusText) {
        mStatusText = statusText;
    }

    bool ResponseBuilder::IsHttpStatusHeaderParsed() const { 
        return mHttpStatusHeaderIsParsed;
    }

    void ResponseBuilder::SetHttpStatusHeaderIsParsed(bool httpStatusHeaderParsed) {
        mHttpStatusHeaderIsParsed = httpStatusHeaderParsed;
    }

    void ResponseBuilder::SetRequest(RequestUPtr aRequest) {
        mRequest = std::move(aRequest);
    }

    size_t ResponseBuilder::AppendToContent(void* content, size_t contentLength) {
        if(mContentBuffer == 0) {
            InitContentBuffer();
        }
        if(ContentBufferHasEnoughSpaceToAppend(contentLength) == false) {
            IncreaseContentBufferFor(
                (GetAvailableSizeInContentBuffer() + mBufferIncreaseRate) < contentLength ? contentLength : mBufferIncreaseRate
            );
        }
        return CopyToContentBuffer(content, contentLength);
    }
    
    void ResponseBuilder::InitContentBuffer() {
        mBufferCapacity = mBufferIncreaseRate;
        if(HeaderExists("Content-Length")) {
            mBufferCapacity = StringUtils::ToUnsignedInt(GetHeaderValue("Content-Length"));
        }
        mContentBuffer = new char[mBufferCapacity];
        mCurrentContentPosition = mContentBuffer;
    }

    size_t ResponseBuilder::GetContentLength() const {
        return mCurrentContentPosition - mContentBuffer;
    }

    size_t ResponseBuilder::GetAvailableSizeInContentBuffer() {
        return mBufferCapacity - GetContentLength();
    }
    
    bool ResponseBuilder::ContentBufferHasEnoughSpaceToAppend(size_t contentLength) {
        return GetAvailableSizeInContentBuffer() >= contentLength;
    }

    void ResponseBuilder::IncreaseContentBufferFor(size_t increaseSize) {
        size_t currentLength = GetContentLength();
        char* oldContentBuffer = mContentBuffer;
        mBufferCapacity += increaseSize;
        mContentBuffer = new char[mBufferCapacity];
        memcpy(mContentBuffer, oldContentBuffer, currentLength);
        mCurrentContentPosition = mContentBuffer + currentLength;
        delete[] oldContentBuffer;
    }

    size_t ResponseBuilder::CopyToContentBuffer(void* content, size_t contentLength) {
        memcpy(mCurrentContentPosition, content, contentLength);
        mCurrentContentPosition += contentLength;
        return contentLength;
    }

    bool ResponseBuilder::HeaderExists(const std::string& headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        return iter != mHeaders.end();
    }

    std::string ResponseBuilder::GetHeaderValue(const std::string& headerKey) {
        typename decltype(mHeaders)::const_iterator iter = mHeaders.find(headerKey);
        if(iter != mHeaders.end()) {
            return iter->second;
        }
        return "";
    }
}
