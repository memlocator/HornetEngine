#include "NetworkingPackage.h"

#include "NetworkPrint.h"
#include "Socket.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<NetworkPrint::Printer>();

		template <>
		extern void ReflectType<Networking::Socket>();

		template <>
		void ReflectPackage<NetworkingPackage>()
		{
			ReflectFromPackage<
				NetworkPrint::Printer,
				Networking::Socket
			>();
		}
	}
}