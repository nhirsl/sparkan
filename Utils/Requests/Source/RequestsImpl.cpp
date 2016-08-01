#include "RequestsImpl.h"

#include "GetRequest.h"
#include "PostRequest.h"
#include "DeleteRequest.h"
#include "IncommingTask.h"

#include "StringUtils.h"
#include "ThreadPoolFactory.h"

#include <algorithm>

namespace Http {
    RequestsImpl::RequestsImpl() {
        ThreadPoolFactoryPtr threadPoolFactory = ThreadPoolFactory::GetInstance();
        if (threadPoolFactory) {
            mIncommingTasks = threadPoolFactory->CreateFixedThreadPool();
            mIncommingTasks->Start();
        }
    }
    
    RequestsImpl::~RequestsImpl() {
    }
    
    void RequestsImpl::Get(
        const std::string& url,
        std::unordered_map<std::string, std::string> queryStringParams,
        std::unordered_map<std::string, std::string> headers,
        std::function<void(ResponseUPtr)> responseHandler) {
        
        GetRequestUPtr getRequest(new GetRequest());
        getRequest->SetUrl(AddQueryStringToUrl(url, queryStringParams));
        getRequest->AddHeaders(headers);
        getRequest->OnResponse(responseHandler);
        
        mIncommingTasks->Enqueue(IncommingTaskPtr(new IncommingTask(std::move(getRequest))));
    }
    
    void RequestsImpl::Get(
        const std::string& url,
        std::unordered_map<std::string, std::string> headers, 
        std::function<void(ResponseUPtr)> responseHandler) {
        
        Get(url, {}, headers, responseHandler);
    }
   
    void RequestsImpl::Get(
        const std::string& url, 
        std::function<void(ResponseUPtr)> responseHandler) {
        
        Get(url, {}, {}, responseHandler);
    }

    void RequestsImpl::Post(const std::string& url, 
                            const std::string& content,
                            std::unordered_map<std::string, std::string> headers, 
                            std::function<void(ResponseUPtr)> responseHandler) {
        
        PostRequestUPtr postRequest(new PostRequest());
        postRequest->SetUrl(url);
        postRequest->AddHeaders(headers);
        postRequest->SetContent(content);
        postRequest->OnResponse(responseHandler);
        
        mIncommingTasks->Enqueue(IncommingTaskPtr(new IncommingTask(std::move(postRequest))));
    }    

    void RequestsImpl::Post(const std::string& url, 
                            const std::string& content,
                            std::function<void(ResponseUPtr)> responseHandler) {
        
        Post(url, content, {}, responseHandler);
    }
    
    void RequestsImpl::Delete(
        const std::string& url, 
        std::unordered_map<std::string, std::string> headers, 
        std::function<void(ResponseUPtr)> responseHandler) {
        
        DeleteRequestUPtr deleteRequest(new DeleteRequest());
        deleteRequest->SetUrl(url);
        deleteRequest->AddHeaders(headers);
        deleteRequest->OnResponse(responseHandler);
        
        mIncommingTasks->Enqueue(IncommingTaskPtr(new IncommingTask(std::move(deleteRequest))));
    }
    
    void RequestsImpl::Delete(
        const std::string& url, 
        std::function<void(ResponseUPtr)> responseHandler) {
        
        Delete(url, {}, responseHandler);
    }
    
    std::string RequestsImpl::AddQueryStringToUrl(const std::string& url, std::unordered_map<std::string, std::string> queryStringParams) {
        if(queryStringParams.size() > 0) {
            std::vector<std::string> params;
            std::transform(queryStringParams.begin(), 
                           queryStringParams.end(), 
                           std::inserter(params, params.begin()), 
                           [](decltype(queryStringParams)::value_type aPair) {
                                return StringUtils::Join(
                                    { StringUtils::EncodeURIComponent(aPair.first), 
                                      StringUtils::EncodeURIComponent(aPair.second) }, "=");
                           });
            std::string queryString = StringUtils::Join(params, "&");
            return StringUtils::Join({url, queryString}, "?");
        } else {
            return url;
        }
    }
}
