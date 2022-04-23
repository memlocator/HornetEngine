#include "NetworkPrint.h"

namespace Engine
{
    namespace NetworkPrint 
    {
        using Engine::Object;

        Reflect_Inherited(Printer, Object,
               Bind_Function(print,
        
                Document("");
                Function_Overload
                (
                    Document("");
                    Returns_Nothing;
        
                    Overload_Parameters
                    (
                        Document("");
                        Function_Parameter(std::string, s);
                    );
        
                    Bind_Parameters_No_Return(print, s);
                );
            );


        );
    }
    
}