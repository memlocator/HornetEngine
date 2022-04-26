#include "Socket.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Networking::Socket>()
		{
			Reflect<Networking::Socket, Object>::Class
			(
				"Socket",
				{ "GameObject", "Networking" },

				Constructor(
					Overload()
				),

				Function(
					"Create",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Networking::Socket, &Networking::Socket::Create>()
				)
			);
		}
	}
}