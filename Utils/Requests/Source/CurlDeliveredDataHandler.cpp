#include "CurlDeliveredDataHandler.h"

#include "ResponseBuilder.h"
#include "StringUtils.h"

#include <string>

namespace Http {
    size_t CurlDeliveredDataHandler::EntityBodyHandler(void* deliveredData, size_t sizeOfUnit, size_t numberOfUnits, void* userData) {
        ResponseBuilder* responseBuilder = (ResponseBuilder*)userData;
        if(responseBuilder) {
            return responseBuilder->AppendToContent(deliveredData, sizeOfUnit * numberOfUnits);
        }
        return 0;
    }
    
    size_t CurlDeliveredDataHandler::HeadersHandler(void* deliveredData, size_t sizeOfUnit, size_t numberOfUnits, void* userData) {
        ResponseBuilder* responseBuilder = (ResponseBuilder*)userData;
        if(responseBuilder) {
            std::string aHeader((char*)deliveredData, sizeOfUnit * numberOfUnits);
            if(responseBuilder->IsHttpStatusHeaderParsed()) {
                if(!StringUtils::Trim(aHeader).empty()) {
                    std::string headerKey;
                    std::string headerValue;
                    ParseHeader(aHeader, &headerKey, &headerValue);
                    responseBuilder->AddHeader(headerKey, headerValue);
                }
            } else {
                std::string httpVersion;
                std::string statusCode;
                std::string statusText;
                ParseStatusHeader(aHeader, &httpVersion, &statusCode, &statusText);
                responseBuilder->SetHttpVersion(httpVersion);
                responseBuilder->SetStatusCode(StringUtils::ToUnsignedInt(statusCode));
                responseBuilder->SetStatusText(statusText);
                responseBuilder->SetHttpStatusHeaderIsParsed(true);
            }
            return sizeOfUnit * numberOfUnits;
        }        
        return 0;
    }

    void CurlDeliveredDataHandler::ParseHeader(const std::string& header, std::string* headerKey, std::string* headerValue) {
        std::vector<std::string> parts = StringUtils::Split(header, ":", 1);
        if(parts.size() == 2) {
            *headerKey = StringUtils::Trim(parts.at(0));
            *headerValue = StringUtils::Trim(parts.at(1));
        }
    }

    void CurlDeliveredDataHandler::ParseStatusHeader(const std::string& statusHeader, std::string* httpVersion, std::string* statusCode, std::string* statusText) {
        std::vector<std::string> parts = StringUtils::Split(statusHeader, " ", 2);
        if(parts.size() == 3) {
            *httpVersion = StringUtils::Trim(parts.at(0));
            *statusCode = StringUtils::Trim(parts.at(1));
            *statusText = StringUtils::Trim(parts.at(2));
        }
    }
}
