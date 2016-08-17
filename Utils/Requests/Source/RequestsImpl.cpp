#include "RequestsImpl.h"

#include "IncommingTask.h"
#include "RequestExecutionContext.h"

#include "Requests/Request.h"
#include "HandlerImpl.h"

#include "ThreadPool/ThreadPoolFactory.h"

#include "StringUtils.h"
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
    
    HandlerUPtr RequestsImpl::Submit(RequestPtr request, ResponseHandlerType responseHandler) {
        RequestExecutionContextPtr requestExecutionContext(new RequestExecutionContext(request));
        mIncommingTasks->Enqueue(
            IncommingTaskPtr(new IncommingTask(requestExecutionContext, std::move(responseHandler)))
        );
        return HandlerImplUPtr(new HandlerImpl(requestExecutionContext));
    }
    
    HandlerUPtr RequestsImpl::Urgent(RequestPtr request, ResponseHandlerType responseHandler) {
        RequestExecutionContextPtr requestExecutionContext(new RequestExecutionContext(request));
        mIncommingTasks->Urgent(
            IncommingTaskPtr(new IncommingTask(requestExecutionContext, std::move(responseHandler)))
        );
        return HandlerImplUPtr(new HandlerImpl(requestExecutionContext));        
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
