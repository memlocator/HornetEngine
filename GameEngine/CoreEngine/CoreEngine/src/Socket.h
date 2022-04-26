#pragma once
#include <vector>
#include "Object.h"
#include "EngineException.h"

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE


#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


namespace Engine
{
    namespace Networking
    {
        class Socket : public Engine::Object
        {
        private:
            std::vector<char> readBuff;
            
            //Asio error handler
            asio::error_code ec;
            //Context - platform specific interface
            asio::io_context context;
            asio::ip::tcp::endpoint endpoint;

            asio::ip::tcp::socket* socket = nullptr;
            std::thread threadContext;

            void unpackData(asio::ip::tcp::socket& socket);
        public:
            virtual ~Socket() {}

            void Create();
        };
    }
}
