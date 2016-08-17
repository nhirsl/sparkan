#include "Requests/Requests.h"
#include "Requests/ForwardDeclarations.h"
#include "Requests/RequestBuilder.h"
#include "Requests/MethodEnum.h"
#include "Requests/Response.h"
#include "Requests/Handler.h"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    Http::RequestsUPtr requests = Http::Requests::CreateInstance();
    if (requests) {        
        Http::RequestBuilderUPtr requestBuilder = Http::RequestBuilder::CreateInstance();
        if (requestBuilder) {
            requestBuilder->SetMethod(Http::Method::GET);
            requestBuilder->SetUrl("http://localhost:5000/osobe/");
            requestBuilder->SetHeader("Accept", "application/json");
            
            Http::HandlerUPtr handler = requests->Submit(requestBuilder->Build(), [](Http::ResponseUPtr response) {
                std::cout << std::string(static_cast<char*>(response->GetContent()), response->GetContentLength()) << std::endl;
            });
            
            // handler->terminate();
        }
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    return 0; 
}
