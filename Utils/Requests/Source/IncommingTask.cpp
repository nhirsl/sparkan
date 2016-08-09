#include "IncommingTask.h"

<<<<<<< HEAD
#include "RequestImpl.h"
#include "Response.h"
#include "ResponseBuilder.h"
#include "CurlDeliveredDataHandler.h"

#include <iostream>

namespace Http {
    IncommingTask::IncommingTask(RequestImplUPtr requestImpl) 
        : mResponseBuilder(new ResponseBuilder())
        , mRequestImpl(std::move(requestImpl))
=======
#include "CurlDeliveredDataHandler.h"
#include "ResponseBuilder.h"

#include "Requests/Request.h"
#include "Requests/Response.h"

namespace Http {
    IncommingTask::IncommingTask(
        RequestUPtr request, 
        ResponseHandlerType responseHandler)
        : mResponseBuilder(new ResponseBuilder())
        , mRequest(std::move(request))
        , mResponseHandler(std::move(responseHandler))
>>>>>>> nebojsakaran
        , mCurlHeaders(0)
        , mCurl(curl_easy_init()) {
    }
    
    IncommingTask::~IncommingTask() {
        curl_easy_cleanup(mCurl);
        mCurl = 0;
    
        curl_slist_free_all(mCurlHeaders);
        mCurlHeaders = 0;
        
        delete mResponseBuilder;
        mResponseBuilder = 0;        
    }
    
    void IncommingTask::Execute() {
        InitCurlParams();

        SetMethod();
        SetUrl();
<<<<<<< HEAD
        SetHttpVersion();

        SetHeaders();

        if (mRequestImpl->GetMethod() == Method::POST || 
            mRequestImpl->GetMethod() == Method::PUT) {
=======
        SetProtocolVersion();

        SetHeaders();

        if (mRequest->GetMethod() == Method::POST || 
            mRequest->GetMethod() == Method::PUT) {
>>>>>>> nebojsakaran
            SetContent();
        }
        
        curl_easy_perform(mCurl);
        
        PerformResponseHandler();
    }
    
    void IncommingTask::InitCurlParams() {
        if (mCurl) {
            curl_easy_setopt(mCurl, CURLOPT_HEADERFUNCTION, &CurlDeliveredDataHandler::HeadersHandler);
            curl_easy_setopt(mCurl, CURLOPT_HEADERDATA, mResponseBuilder);

            curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, &CurlDeliveredDataHandler::EntityBodyHandler);
            curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, mResponseBuilder);            

            curl_easy_setopt(mCurl, CURLOPT_FOLLOWLOCATION, 1L);            
        }
    }
    
    void IncommingTask::SetMethod() {
        if (mCurl) {
<<<<<<< HEAD
            switch(mRequestImpl->GetMethod()) {
=======
            switch(mRequest->GetMethod()) {
>>>>>>> nebojsakaran
            case Method::POST:   curl_easy_setopt(mCurl, CURLOPT_POST, 1L);                  break;
            case Method::DELETE: curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "DELETE");   break;
            case Method::PUT:    curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "PUT");      break; // CURLOPT_PUT is deprecated
            }
        }        
    }
    
    void IncommingTask::SetUrl() {
        if (mCurl) {
<<<<<<< HEAD
            curl_easy_setopt(mCurl, CURLOPT_URL, mRequestImpl->GetUrl().c_str());
        }
    }
    
    void IncommingTask::SetHttpVersion() {
        
=======
            curl_easy_setopt(mCurl, CURLOPT_URL, mRequest->GetUrl().c_str());
        }
    }
    
    void IncommingTask::SetProtocolVersion() {
        ProtocolVersion protocolVersion = mRequest->GetProtocolVersion();
        switch (protocolVersion) {
        case ProtocolVersion::HTTP_1_0: 
            curl_easy_setopt(mCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
            break;
        case ProtocolVersion::HTTP_1_1: 
            curl_easy_setopt(mCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
            break;
        case ProtocolVersion::HTTP_2: 
            curl_easy_setopt(mCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
            break;
        default: 
            curl_easy_setopt(mCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_NONE); // libcurl will use whatever it thinks fit
        }
>>>>>>> nebojsakaran
    }
    
    void IncommingTask::SetHeaders() {
        if (mCurlHeaders) {
<<<<<<< HEAD
            std::unordered_map<std::string, std::string> headersMap = mRequestImpl->GetHeaders();
=======
            std::map<std::string, std::string> headersMap = mRequest->GetHeaders();
>>>>>>> nebojsakaran
            if (headersMap.size() > 0) {
                typename decltype(headersMap)::iterator iter = headersMap.begin();
                typename decltype(headersMap)::iterator end = headersMap.end();
                for(; iter != end; iter++) {
                    mCurlHeaders = curl_slist_append(mCurlHeaders, std::string(iter->first + ": " + iter->second).c_str());
                }
                curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, mCurlHeaders);
            }
        }
    }
    
    void IncommingTask::SetContent() {
        if (mCurl) {
<<<<<<< HEAD
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, mRequestImpl->GetContent());
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDSIZE, mRequestImpl->GetContentLength());
=======
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, mRequest->GetContent());
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDSIZE, mRequest->GetContentLength());
>>>>>>> nebojsakaran
        }
    }
    
    void IncommingTask::PerformResponseHandler() {
<<<<<<< HEAD
        std::function<void(ResponseUPtr)> resposneHandler = mRequestImpl->GetResponseHandler();
        mResponseBuilder->SetRequest(std::move(mRequestImpl));
        resposneHandler(mResponseBuilder->Build());
=======
        mResponseBuilder->SetRequest(std::move(mRequest));
        mResponseHandler(mResponseBuilder->Build());
>>>>>>> nebojsakaran
    }
}
