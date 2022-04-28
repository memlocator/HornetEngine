#pragma once

#include "LuaInput.h"

namespace GraphicsEngine
{
	class InputSubscription : public Engine::InputObject
	{
	public:
		~InputSubscription();

		void Initialize();
		void Update(Float);
		bool HasFocus(Enum::BoundDevice device) const;

		void Subscribe(const std::shared_ptr<Engine::InputObject>& input);

	private:
		bool ChangedThisFrame = false;
		int BeganConnection = -1;
		int ChangedConnection = -1;
		int EndedConnection = -1;
		std::shared_ptr<Engine::InputObject> Input;

		void UpdateState();
	};

	class InputSubscriber : public Engine::Object
	{
	public:
		bool Focused[Enum::BoundDevice::Count] = { false };
		bool FocusedLast[Enum::BoundDevice::Count] = { false };

		void Initialize();
		void Update(Float);

		std::shared_ptr<InputSubscription> Subscribe(const std::shared_ptr<Engine::InputObject>& input);

		void SetFocus(Enum::BoundDevice device, bool focus);
		bool HasFocus(Enum::BoundDevice device) const { return Focused[device]; }
	};
}