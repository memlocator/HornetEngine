#pragma once

#include "Object.h"

namespace Engine
{
	class InputObject;

	namespace Editor
	{
		class Selector : public Object
		{
		public:
			std::weak_ptr<InputObject> MousePosition;
			std::weak_ptr<InputObject> SelectButton;
			std::weak_ptr<InputObject> RequiredModifierKey;
		};
	}
}