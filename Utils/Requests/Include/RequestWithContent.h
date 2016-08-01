#pragma once

#include "RequestImpl.h"

#include <cstddef>

namespace Http {
    class RequestWithContent : public RequestImpl {
    public:
        RequestWithContent();
        
        virtual ~RequestWithContent();

        virtual void* GetContent() override;
        
        virtual size_t GetContentLength() override;
        
        virtual void SetContent(const std::string& content);
        
        virtual void SetContent(void* content, size_t contentLength);
        
    private:
        void* mContent;
        size_t mContentLength;
    };
}
