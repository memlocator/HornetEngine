#pragma once

#include "Object.h"

namespace Engine
{
    namespace NetworkPrint 
    {
        class Printer : public Engine::Object
        {
        public:
            virtual ~Printer() {}

            void print(std::string str)
            {
                std::cout << "Print from C++: " << str << std::endl;
            }
        };
    }
}