#include "Fonts.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Fonts>()
		{
			Reflect<Fonts, Object>::Class
			(
				"Fonts",
				{ "GameObject" },

				Constructor(
					Overload()
				)
			);
		}
	}
}