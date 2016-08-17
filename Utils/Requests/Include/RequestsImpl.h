#pragma once

#include "Requests/Requests.h"

#include "ThreadPool/ThreadPool.h"

#include <map>

namespace Http {
    class RequestsImpl : public Requests {
    public:
        RequestsImpl();
        
        virtual ~RequestsImpl();

        HandlerUPtr Submit(RequestPtr request, ResponseHandlerType responseHandler) override;
        
        HandlerUPtr Urgent(RequestPtr request, ResponseHandlerType responseHandler) override;
        
    private:
        std::string AddQueryStringToUrl(const std::string& url, std::map<std::string, std::string> queryStringParams);
        
        ThreadPoolUPtr mIncommingTasks;
    };
}
