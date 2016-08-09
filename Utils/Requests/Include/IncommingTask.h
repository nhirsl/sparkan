#pragma once

<<<<<<< HEAD
#include "ForwardDeclarations.h"

#include "Task.h"
=======
#include "Requests/ForwardDeclarations.h"

#include "ThreadPool/Task.h"
#include "ThreadPool/ForwardDeclarations.h"
>>>>>>> nebojsakaran

#include <curl/curl.h>

namespace Http {
    class IncommingTask : public ::Task {
    public:
<<<<<<< HEAD
        IncommingTask(RequestImplUPtr requestImpl);
=======
        IncommingTask(RequestUPtr requestImpl, ResponseHandlerType responseHandler);
>>>>>>> nebojsakaran
        
        ~IncommingTask();
        
        void Execute() override;
        
    private:
        void InitCurlParams();
        void SetMethod();
        void SetUrl();
<<<<<<< HEAD
        void SetHttpVersion();
=======
        void SetProtocolVersion();
>>>>>>> nebojsakaran
        void SetHeaders();
        void SetContent();
        void PerformResponseHandler();
        
        ResponseBuilder* mResponseBuilder;
<<<<<<< HEAD
        RequestImplUPtr mRequestImpl;
=======
        
        RequestUPtr mRequest;
        
        ResponseHandlerType mResponseHandler;
>>>>>>> nebojsakaran
        
        struct curl_slist* mCurlHeaders;
        CURL* mCurl;
    };    
}
<<<<<<< HEAD

=======
>>>>>>> nebojsakaran
