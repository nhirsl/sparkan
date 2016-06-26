#include "RequestPerformer.h"

#include "RequestImpl.h"
#include "Response.h"
#include "ResponseBuilder.h"
#include "MethodEnum.h"
#include "CurlDeliveredDataHandler.h"

#include <curl/curl.h>
#include <iostream>

namespace Http {
    void RequestPerformer::Init() {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    
    void RequestPerformer::Perform(RequestImplUPtr requestImpl) {
        CURL* curl = 0;
        curl = curl_easy_init();
        if(curl) {
            ResponseBuilder* aResponseBuilder = new ResponseBuilder();
            
            curl_easy_setopt(curl, CURLOPT_URL, requestImpl->GetUrl().c_str());
            
            switch(requestImpl->GetMethod()) {
            case Method::POST:   curl_easy_setopt(curl, CURLOPT_POST, 1L);                  break;
            case Method::DELETE: curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");   break;
            case Method::PUT:    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");      break;
            }

            if (requestImpl->GetMethod() == Method::POST || 
                requestImpl->GetMethod() == Method::PUT) {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestImpl->GetContent());
                curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestImpl->GetContentLength());
            }
            
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &CurlDeliveredDataHandler::HeadersHandler);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, aResponseBuilder);
            
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlDeliveredDataHandler::EntityBodyHandler);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, aResponseBuilder);
            
            std::unordered_map<std::string, std::string> headersMap = requestImpl->GetHeaders();
            struct curl_slist* headers = 0;
            if(headersMap.size() > 0) {
                typename decltype(headersMap)::iterator iter = headersMap.begin();
                typename decltype(headersMap)::iterator end = headersMap.end();
                for(; iter != end; iter++) {
                    headers = curl_slist_append(headers, std::string(iter->first + ": " + iter->second).c_str());
                }
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            }

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            
            curl_easy_perform(curl);

            if (headers) {
                curl_slist_free_all(headers);
            }
            
            curl_easy_cleanup(curl);
            
            std::function<void(ResponseUPtr)> resposneHandler = requestImpl->GetResponseHandler();
            
            aResponseBuilder->SetRequest(std::move(requestImpl));
            
            ResponseUPtr response = aResponseBuilder->Build();
            
            delete aResponseBuilder;
            aResponseBuilder = 0;
            
            resposneHandler(std::move(response));
        }
    }
}
