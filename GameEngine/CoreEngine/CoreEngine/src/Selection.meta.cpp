#include "Selection.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Editor;

		template <>
		void ReflectType<Selection>()
		{
			Reflect<Selection, Object>::Class
			(
				"Selection",
				{ "GameObject" },

				Constructor(
					Overload()
				)
			);
		}
	}
}