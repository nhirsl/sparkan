#include "IncommingTask.h"

#include "RequestImpl.h"
#include "Response.h"
#include "ResponseBuilder.h"
#include "CurlDeliveredDataHandler.h"

#include <iostream>

namespace Http {
    IncommingTask::IncommingTask(RequestImplUPtr requestImpl) 
        : mResponseBuilder(new ResponseBuilder())
        , mRequestImpl(std::move(requestImpl))
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
        SetHttpVersion();

        SetHeaders();

        if (mRequestImpl->GetMethod() == Method::POST || 
            mRequestImpl->GetMethod() == Method::PUT) {
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
            switch(mRequestImpl->GetMethod()) {
            case Method::POST:   curl_easy_setopt(mCurl, CURLOPT_POST, 1L);                  break;
            case Method::DELETE: curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "DELETE");   break;
            case Method::PUT:    curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "PUT");      break; // CURLOPT_PUT is deprecated
            }
        }        
    }
    
    void IncommingTask::SetUrl() {
        if (mCurl) {
            curl_easy_setopt(mCurl, CURLOPT_URL, mRequestImpl->GetUrl().c_str());
        }
    }
    
    void IncommingTask::SetHttpVersion() {
        
    }
    
    void IncommingTask::SetHeaders() {
        if (mCurlHeaders) {
            std::unordered_map<std::string, std::string> headersMap = mRequestImpl->GetHeaders();
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
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, mRequestImpl->GetContent());
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDSIZE, mRequestImpl->GetContentLength());
        }
    }
    
    void IncommingTask::PerformResponseHandler() {
        std::function<void(ResponseUPtr)> resposneHandler = mRequestImpl->GetResponseHandler();
        mResponseBuilder->SetRequest(std::move(mRequestImpl));
        resposneHandler(mResponseBuilder->Build());
    }
}
