#include "NetworkPrint.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<NetworkPrint::Printer> ()
		{
			Reflect<NetworkPrint::Printer, Object>::Class
			(
				"Printer",
				{ "GameObject", "NetworkPrint" },

				Constructor(
					Overload()
				),

				Function(
					"print",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<std::string>("str")
					).Bind<NetworkPrint::Printer, &NetworkPrint::Printer::print>()
				)
			);
		}
	}
}