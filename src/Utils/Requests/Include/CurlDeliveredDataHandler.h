#pragma once

#include <cstddef>
#include <string>

namespace Http {
    class CurlDeliveredDataHandler final {
    public:
        static size_t EntityBodyHandler(void* deliveredData, size_t sizeOfUnit, size_t numberOfUnits, void* userData);

        static size_t HeadersHandler(void* deliveredData, size_t sizeOfUnit, size_t numberOfUnits, void* userData);
        
    private:
        static void ParseHeader(const std::string& header, std::string* headerKey, std::string* headerValue);
        
        static void ParseStatusHeader(const std::string& statusHeader, std::string* httpVersion, std::string* statusCode, std::string* statusText);
    };
}
