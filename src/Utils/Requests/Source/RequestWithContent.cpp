#include "RequestWithContent.h"

#include <cstring>

namespace Http {
    RequestWithContent::RequestWithContent() 
        : mContent(0)
        , mContentLength(0) {
    }

    RequestWithContent::~RequestWithContent() {
        delete[] (char*)mContent;
        mContent = 0;
    }

    void* RequestWithContent::GetContent() {
        return mContent;
    }
    
    size_t RequestWithContent::GetContentLength() {
        return mContentLength;
    }

    void RequestWithContent::SetContent(const std::string& content) {
        SetContent((void*)content.c_str(), content.length() * sizeof(std::string::value_type));
    }

    void RequestWithContent::SetContent(void* content, size_t contentLength) {
        mContent = new char[contentLength];
        memcpy(mContent, content, contentLength);
        
        mContentLength = contentLength;
    }
}
