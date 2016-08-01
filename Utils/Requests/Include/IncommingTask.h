#pragma once

#include "ForwardDeclarations.h"

#include "Task.h"

#include <curl/curl.h>

namespace Http {
    class IncommingTask : public ::Task {
    public:
        IncommingTask(RequestImplUPtr requestImpl);
        
        ~IncommingTask();
        
        void Execute() override;
        
    private:
        void InitCurlParams();
        void SetMethod();
        void SetUrl();
        void SetHttpVersion();
        void SetHeaders();
        void SetContent();
        void PerformResponseHandler();
        
        ResponseBuilder* mResponseBuilder;
        RequestImplUPtr mRequestImpl;
        
        struct curl_slist* mCurlHeaders;
        CURL* mCurl;
    };    
}

