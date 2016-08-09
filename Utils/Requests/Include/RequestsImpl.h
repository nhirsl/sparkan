#pragma once

#include "Requests/Requests.h"

#include "ThreadPool/ThreadPool.h"

#include <map>

namespace Http {
    class RequestsImpl : public Requests {
    public:
        RequestsImpl();
        
        virtual ~RequestsImpl();

        virtual void Submit(RequestUPtr request, ResponseHandlerType responseHandler) override;
        
        virtual void Urgent(RequestUPtr request, ResponseHandlerType responseHandler) override;
        
    private:
        std::string AddQueryStringToUrl(const std::string& url, std::map<std::string, std::string> queryStringParams);
        
        ThreadPoolUPtr mIncommingTasks;
    };
}
