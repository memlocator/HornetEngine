#include "Alignment.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::Alignment>()
		{
			Reflect<Enum::Alignment>::Enum
			(
				"Alignment",
				Value<Enum::Alignment::Minimum>("Minimum"),
				Value<Enum::Alignment::Center>("Center"),
				Value<Enum::Alignment::Maximum>("Maximum")
			);
		}
	}
}