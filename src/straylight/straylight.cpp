// #include <ixwebsocket/IXNetSystem.h>
// #include <ixwebsocket/IXWebSocket.h>
// #include <ixwebsocket/IXUserAgent.h>

#include "/workspaces/dev_playground_c/src/straylight/client_wss.hpp"
// #include "server_wss.hpp"
#include "straylight.h"

// using WssServer = SimpleWeb::SocketServer<SimpleWeb::WSS>;
using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

using namespace std;

Straylight::Straylight() {
    spdlog::info("Straylight Running...");

    WssClient client("wss://stream.binance.com:9443/ws/bnbbtc@depth", false);
    client.on_message = [](shared_ptr<WssClient::Connection> connection, shared_ptr<WssClient::InMessage> in_message) {
        cout << "Client: Message received: \"" << in_message->string() << "\"" << endl;

        cout << "Client: Sending close connection" << endl;
        connection->send_close(1000);
    };

    client.on_close = [](shared_ptr<WssClient::Connection> /*connection*/, int status, const string & /*reason*/) {
        cout << "Client: Closed connection with status code " << status << endl;
    };

    // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    client.on_error = [](shared_ptr<WssClient::Connection> /*connection*/, const SimpleWeb::error_code &ec) {
        cout << "Client: Error: " << ec << ", error message: " << ec.message() << endl;
    };

    client.start();

    spdlog::info("Straylight Finished.");

    while (true) {  }
}

void Straylight::add(BinanceOrder newOrder){

}



/*

Websocket: wss://stream.binance.com:9443/ws/bnbbtc@depth

Input:
- price
- quantity

# Need
- Print: top 5           O(1)
- Delete at any location O(log n)
- Update at any location O(1)?
- Add at any location    O(log n)

- Sorted


*/