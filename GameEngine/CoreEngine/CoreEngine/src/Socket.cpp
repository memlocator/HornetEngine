#include "Socket.h"

void Engine::Networking::Socket::Create()
{
    asio::error_code ec;

    //Context - platform specific interface
    asio::io_context context;

    //Target to connect to
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.32", ec), 80);

    //TCP socket
    asio::ip::tcp::socket socket(context);

    //Establish connection
    socket.connect(endpoint, ec);


    if (ec)
        throw EngineException(ec.message().data());
    else
        std::cout << "Connection established!" << std::endl;
}
