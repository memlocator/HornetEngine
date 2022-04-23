#include "CollisionGroup.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		void ReflectType<CollisionGroup>()
		{
			Reflect<CollisionGroup, Object>::Class
			(
				"CollisionGroup",
				{ "GameObject", "Physics" },

				Function(
					"AddInteraction",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Object>&>("group"), // TODO: change type when reflection is replaced
						Argument<Enum::InteractionType>("type")
					).Bind<CollisionGroup, &CollisionGroup::AddInteraction>()
				),

				Function(
					"GetInteraction",
					Overload(
						Const,
						Returns<Enum::InteractionType>(),
						Argument<const std::shared_ptr<Object>&>("group")
					).Bind<CollisionGroup, &CollisionGroup::GetInteraction>()
				)
			);
		}

		template <>
		void ReflectType<Enum::InteractionType>()
		{
			Reflect<Enum::InteractionType>::Enum
			(
				"InteractionType",
				Value<Enum::InteractionType::None>("None"),
				Value<Enum::InteractionType::Detect>("Detect"),
				Value<Enum::InteractionType::Resolve>("Resolve")
			);
		}
	}
}