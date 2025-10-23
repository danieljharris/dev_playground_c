#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include "straylight.h"

Straylight::Straylight() {
    spdlog::info("Straylight Running...");

    ix::initNetSystem();
    ix::WebSocket webSocket;
    string url("wss://stream.binance.com:9443/ws/bnbbtc@depth");
    webSocket.setUrl(url);

    webSocket.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << msg->str << std::endl;
                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Open)
            {
                std::cout << "Connection established" << std::endl;
                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Error)
            {
                // Maybe SSL is not configured properly
                std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
                std::cout << "> " << std::flush;
            }
        }
    );

    webSocket.start();


    spdlog::info("Straylight Finished.");
}

// static void Straylight::handleWebsocket(const std::string & message) {
//     // spdlog::info("Got message: {}", {});
//     std::cout << "Here";
// }



/*

Websocket: wss://stream.binance.com:9443/ws/bnbbtc@depth

Input:
- price
- quantity

# Need
- Print: top 5
- Delete at any location
- Update at any location
- Add at any location

- Sorted


*/