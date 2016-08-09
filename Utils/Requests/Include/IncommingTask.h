#pragma once

#include "Requests/ForwardDeclarations.h"

#include "ThreadPool/Task.h"
#include "ThreadPool/ForwardDeclarations.h"

#include <curl/curl.h>

namespace Http {
    class IncommingTask : public ::Task {
    public:
        IncommingTask(RequestUPtr requestImpl, ResponseHandlerType responseHandler);
        
        ~IncommingTask();
        
        void Execute() override;
        
    private:
        void InitCurlParams();
        void SetMethod();
        void SetUrl();
        void SetProtocolVersion();
        void SetHeaders();
        void SetContent();
        void PerformResponseHandler();
        
        ResponseBuilder* mResponseBuilder;
        
        RequestUPtr mRequest;
        
        ResponseHandlerType mResponseHandler;
        
        struct curl_slist* mCurlHeaders;
        CURL* mCurl;
    };    
}
