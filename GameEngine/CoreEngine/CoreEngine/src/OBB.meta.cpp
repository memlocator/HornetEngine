#include "OBB.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<OBB>()
		{
			Reflect<OBB>::Type(
				"OBB",

				Member<Bind(&OBB::Size)>("Size"),
				Member<Bind(&OBB::Center)>("Center"),
				Member<Bind(&OBB::Transformation)>("Transformation")
			);
		}
	}
}