#include "Socket.h"

void Engine::Networking::Socket::unpackData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(readBuff.data(), readBuff.size()), 
        [&](std::error_code ec, std::size_t len)
        {
            if (!ec)
            {
                std::cout << "\n\nRead " << len << " bytes\n\n";

                for (int i = 0; i < len; i++)
                    std::cout <<  readBuff[i];

                //Only runs once there is some actual data to read - runs async
                unpackData(socket);
            }
        }
    );
}

void Engine::Networking::Socket::Create()
{
    std::cout << "============== RUNNING SOCKET CREATE" << std::endl;

    //Create fake work to keep it occupied
    asio::io_context::work idleWork(context);

    //multithread the context
    threadContext = std::thread([&]() {context.run(); });
    threadContext.detach();

    //Target to connect to
    endpoint = asio::ip::tcp::endpoint(asio::ip::make_address("93.184.216.32", ec), 80);

    //TCP socket
    socket = new asio::ip::tcp::socket(context);

    //Establish connection
    socket->connect(endpoint, ec);


    if (ec)
        throw EngineException(ec.message().data());
    else
        std::cout << "Connection established!" << std::endl;

    if (socket -> is_open()) //if there's a valid socket file desc
    {
        //Primes the context, executes only once there's data.
        unpackData(*socket);

        std::string request =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket->write_some(asio::buffer(request.data(), request.size()), ec);

        context.stop();
        if (threadContext.joinable())
            threadContext.join();
        std::cout << "============== RUNNING SOCKET END" << std::endl;
    }
}
