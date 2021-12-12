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

            void Initialize() {};
            void Update(float) {}

            void print(std::string str)
            {
                std::cout << "Print from C++: " << str << std::endl;
            }


            Instantiable;
            Inherits_Class(Object);

            Reflected(Printer);
        };
    }
    

}