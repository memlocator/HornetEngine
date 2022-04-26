#pragma once

#include "Object.h"

#include <map>

namespace Engine
{
	namespace Physics
	{
		class CollisionGroup : public Object
		{
		public:
			struct InteractionTypeEnum
			{
				enum InteractionType
				{
					None,
					Detect,
					Resolve
				};
			};

			typedef InteractionTypeEnum::InteractionType InteractionType;

			~CollisionGroup();

			void AddInteraction(const std::shared_ptr<CollisionGroup>& group, InteractionType type);
			InteractionType GetInteraction(const std::shared_ptr<CollisionGroup>& group) const;

		private:
			typedef std::pair<std::weak_ptr<Object>, InteractionType> InteractionPair;
			typedef std::map<int, InteractionPair> GroupMap;

			GroupMap Interactions;

			void AddInteractionRegistry(const std::shared_ptr<Object>& group, InteractionType type);
		};
	}
}

namespace Enum
{
	typedef Engine::Physics::CollisionGroup::InteractionType InteractionType;
}