#pragma once

#include "Requests/ForwardDeclarations.h"

#include "ThreadPool/Task.h"
#include "ThreadPool/ForwardDeclarations.h"

#include <curl/curl.h>

namespace Http {
    class IncommingTask : public ::Task {
    public:
        IncommingTask(
            RequestExecutionContextPtr requestExecutionContext, 
            ResponseHandlerType responseHandler
        );
        
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
                
        ResponseHandlerType mResponseHandler;
        
        RequestExecutionContextPtr mRequestExecutionContext;
        
        struct curl_slist* mCurlHeaders;
        CURL* mCurl;
    };    
}
