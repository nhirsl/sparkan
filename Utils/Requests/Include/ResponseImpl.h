#pragma once

<<<<<<< HEAD
#include "Response.h"
=======
#include "Requests/Response.h"
>>>>>>> nebojsakaran

namespace Http {
    class ResponseImpl : public Response {
    public:
        ResponseImpl();
        
        virtual ~ResponseImpl();
        
        virtual void* GetContent() override; 
        
        virtual size_t GetContentLength() override;
        
        virtual std::string GetContentType() override;
        
        virtual std::string GetHeaderValue(std::string headerKey) override;
        
<<<<<<< HEAD
        virtual std::unordered_map<std::string, std::string> GetHeaders() override;
        
        virtual bool HeaderExists(const std::string& headerKey) override;
        
        virtual std::string GetHttpVersion() override;
=======
        virtual std::map<std::string, std::string> GetHeaders() override;
        
        virtual bool HeaderExists(const std::string& headerKey) override;
        
        virtual ProtocolVersion GetProtocolVersion() override;
>>>>>>> nebojsakaran
        
        virtual unsigned int GetStatusCode() override;
        
        virtual std::string GetStatusText() override;
        
        virtual RequestUPtr GetRequest() override;
        
<<<<<<< HEAD
        void SetHttpVersion(const std::string& httpVersion);
=======
        void SetProtocolVersion(ProtocolVersion protocolVersion);
>>>>>>> nebojsakaran
        
        void SetStatusCode(unsigned int statusCode);
        
        void SetStatusText(const std::string& statusText);
        
<<<<<<< HEAD
        void SetHeaders(std::unordered_map<std::string, std::string> headers);
=======
        void SetHeaders(std::map<std::string, std::string> headers);
>>>>>>> nebojsakaran
        
        void SetContent(void* content, size_t contentLength);
        
        void SetRequest(RequestUPtr aRequest);
        
    private:
        RequestUPtr mRequest;
        
<<<<<<< HEAD
        std::string mHttpVersion;
=======
        ProtocolVersion mProtocolVersion;
>>>>>>> nebojsakaran
        unsigned int mStatusCode;
        std::string mStatusText;
        
        void* mContent;
        size_t mContentLength;
        
<<<<<<< HEAD
        std::unordered_map<std::string, std::string> mHeaders;
=======
        std::map<std::string, std::string> mHeaders;
>>>>>>> nebojsakaran
    };
}
