#include "IncommingTask.h"

#include "CurlDeliveredDataHandler.h"
#include "ResponseBuilder.h"

#include "RequestExecutionContext.h"

#include "Requests/Request.h"
#include "Requests/Response.h"

namespace Http {
    IncommingTask::IncommingTask(
        RequestExecutionContextPtr requestExecutionContext,
        ResponseHandlerType responseHandler)
        : mRequestExecutionContext(requestExecutionContext)
        , mResponseHandler(std::move(responseHandler))
        , mCurlHeaders(0)
        , mCurl(curl_easy_init()) {
    }
    
    IncommingTask::~IncommingTask() {
        curl_easy_cleanup(mCurl);
        mCurl = 0;
    
        curl_slist_free_all(mCurlHeaders);
        mCurlHeaders = 0;
    }
    
    void IncommingTask::Execute() {
        InitCurlParams();

        SetMethod();
        SetUrl();
        SetProtocolVersion();

        SetHeaders();

        if (mRequestExecutionContext->getRequest()->GetMethod() == Method::POST || 
            mRequestExecutionContext->getRequest()->GetMethod() == Method::PUT) {
            SetContent();
        }        
        
        curl_easy_perform(mCurl);
        
        if (mRequestExecutionContext->getExecutionStatus() != RequestExecutionStatus::TERMINATED) {
            PerformResponseHandler();
        }
    }
    
    void IncommingTask::InitCurlParams() {
        if (mCurl) {
            curl_easy_setopt(mCurl, CURLOPT_HEADERFUNCTION, &CurlDeliveredDataHandler::HeadersHandler);
            curl_easy_setopt(mCurl, CURLOPT_HEADERDATA, &mRequestExecutionContext);

            curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, &CurlDeliveredDataHandler::EntityBodyHandler);
            curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &mRequestExecutionContext);            

            curl_easy_setopt(mCurl, CURLOPT_FOLLOWLOCATION, mRequestExecutionContext->getRequest()->getFollowLocation());
        }
    }
    
    void IncommingTask::SetMethod() {
        if (mCurl) {
            switch(mRequestExecutionContext->getRequest()->GetMethod()) {
            case Method::POST:   curl_easy_setopt(mCurl, CURLOPT_POST, 1L);                  break;
            case Method::DELETE: curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "DELETE");   break;
            case Method::PUT:    curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "PUT");      break; // CURLOPT_PUT is deprecated
            }
        }        
    }
    
    void IncommingTask::SetUrl() {
        if (mCurl) {
            curl_easy_setopt(mCurl, CURLOPT_URL, mRequestExecutionContext->getRequest()->GetUrl().c_str());
        }
    }
    
    void IncommingTask::SetProtocolVersion() {
        ProtocolVersion protocolVersion = mRequestExecutionContext->getRequest()->GetProtocolVersion();
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
    }
    
    void IncommingTask::SetHeaders() {
        if (mCurlHeaders) {
            std::map<std::string, std::string> headersMap = mRequestExecutionContext->getRequest()->GetHeaders();
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
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, mRequestExecutionContext->getRequest()->GetContent());
            curl_easy_setopt(mCurl, CURLOPT_POSTFIELDSIZE, mRequestExecutionContext->getRequest()->GetContentLength());
        }
    }
    
    void IncommingTask::PerformResponseHandler() {
        ResponseBuilderPtr resposneBuilder = mRequestExecutionContext->getResponseBuilder();
        if (resposneBuilder) {
            resposneBuilder->SetRequest(mRequestExecutionContext->getRequest());
            mResponseHandler(resposneBuilder->Build());
        }
    }
}
