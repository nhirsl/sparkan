#include "RequestsImpl.h"

#include "IncommingTask.h"
#include "StringUtils.h"

#include "Requests/Request.h"

#include "ThreadPool/ThreadPoolFactory.h"

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
        mIncommingTasks->Close();
    }
    
    void RequestsImpl::Submit(RequestUPtr request, ResponseHandlerType responseHandler) {
        mIncommingTasks->Enqueue(
            IncommingTaskPtr(new IncommingTask(std::move(request), std::move(responseHandler)))
        );
    }
    
    void RequestsImpl::Urgent(RequestUPtr request, ResponseHandlerType responseHandler) {
        mIncommingTasks->Urgent(
            IncommingTaskPtr(new IncommingTask(std::move(request), std::move(responseHandler)))
        );
    }
    
    std::string RequestsImpl::AddQueryStringToUrl(const std::string& url, std::map<std::string, std::string> queryStringParams) {
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
