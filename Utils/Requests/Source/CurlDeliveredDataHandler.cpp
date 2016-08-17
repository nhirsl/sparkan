#include "CurlDeliveredDataHandler.h"

#include "ResponseBuilder.h"
#include "StringUtils.h"
#include "RequestExecutionContext.h"
#include "RequestExecutionStatus.h"

#include <string>

namespace Http {
    size_t CurlDeliveredDataHandler::EntityBodyHandler(void* deliveredData, size_t sizeOfUnit, size_t numberOfUnits, void* userData) {
        RequestExecutionContextPtr executionContext = *(static_cast<RequestExecutionContextPtr*>(userData));
        if (executionContext && executionContext->getExecutionStatus() != RequestExecutionStatus::TERMINATED) {
            ResponseBuilderPtr responseBuilder = executionContext->getResponseBuilder();
            if (responseBuilder) {
                return responseBuilder->AppendToContent(deliveredData, sizeOfUnit * numberOfUnits);
            }            
        }
        return 0;
    }

    size_t CurlDeliveredDataHandler::HeadersHandler(void* deliveredData, size_t sizeOfUnit, size_t numberOfUnits, void* userData) {
        RequestExecutionContextPtr executionContext = *(static_cast<RequestExecutionContextPtr*>(userData));
        if (executionContext && executionContext->getExecutionStatus() != RequestExecutionStatus::TERMINATED) {
            ResponseBuilderPtr responseBuilder = executionContext->getResponseBuilder();
            if (responseBuilder) {
                std::string aHeader(static_cast<char*>(deliveredData), sizeOfUnit * numberOfUnits);
                if(responseBuilder->IsHttpStatusHeaderParsed()) {
                    if(!StringUtils::Trim(aHeader).empty()) {
                        std::string headerKey;
                        std::string headerValue;
                        ParseHeader(aHeader, &headerKey, &headerValue);
                        responseBuilder->AddHeader(headerKey, headerValue);
                    }
                } else {
                    std::string protocolVersionString;
                    std::string statusCode;
                    std::string statusText;
                    ParseStatusHeader(aHeader, &protocolVersionString, &statusCode, &statusText);
                    responseBuilder->SetProtocolVersion(ToProtocolVersion(protocolVersionString));
                    responseBuilder->SetStatusCode(StringUtils::ToUnsignedInt(statusCode));
                    responseBuilder->SetStatusText(statusText);
                    responseBuilder->SetHttpStatusHeaderIsParsed(true);
                }
                return sizeOfUnit * numberOfUnits;
            }        
        }
        return 0;
    }

    void CurlDeliveredDataHandler::ParseHeader(const std::string& header, std::string* headerKey, std::string* headerValue) {
        std::vector<std::string> parts = StringUtils::Split(header, ":", 1);
        if (parts.size() == 2) {
            *headerKey = StringUtils::Trim(parts.at(0));
            *headerValue = StringUtils::Trim(parts.at(1));
        }
    }

    void CurlDeliveredDataHandler::ParseStatusHeader(const std::string& statusHeader, std::string* protocolVersionString, std::string* statusCode, std::string* statusText) {
        std::vector<std::string> parts = StringUtils::Split(statusHeader, " ", 2);
        if (parts.size() == 3) {
            *protocolVersionString = StringUtils::Trim(parts.at(0));
            *statusCode = StringUtils::Trim(parts.at(1));
            *statusText = StringUtils::Trim(parts.at(2));
        }
    }
    
    ProtocolVersion CurlDeliveredDataHandler::ToProtocolVersion(const std::string& version) {
        if (StringUtils::CaseInsensitiveEqual(version, "HTTP/1.1")) {
            return ProtocolVersion::HTTP_1_1;
        } else if (StringUtils::CaseInsensitiveEqual(version, "HTTP/1.0")) {
            return ProtocolVersion::HTTP_1_0;
        } else {
            return ProtocolVersion::HTTP_2;
        }
    }
}
