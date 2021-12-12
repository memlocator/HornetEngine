#pragma once
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
        public:
            virtual ~Socket() {}

            void Initialize() {};
            void Update(float) {}

            void Create();
            
            

            Instantiable;
            Inherits_Class(Object);

            Reflected(Socket);
        };
    }
}
