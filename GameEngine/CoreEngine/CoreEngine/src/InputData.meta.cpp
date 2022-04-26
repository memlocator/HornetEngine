#include "LuaInput.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<InputObject>()
		{
			Reflect<InputObject, Object>::Class
			(
				"InputObject",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"GetState",
					Overload(
						Const,
						Returns<bool>(),
						Argument<Enum::BoundDevice, Default(Enum::BoundDevice::Any)>("device")
					).Bind<InputObject, &InputObject::GetState>()
				),

				Function(
					"GetStateChanged",
					Overload(
						Const,
						Returns<bool>(),
						Argument<Enum::BoundDevice, Default(Enum::BoundDevice::Any)>("device")
					).Bind<InputObject, &InputObject::GetStateChanged>()
				),

				Function(
					"GetStateEnum",
					Overload(
						Const,
						Returns<Enum::InputState>(),
						Argument<Enum::BoundDevice, Default(Enum::BoundDevice::Any)>("device")
					).Bind<InputObject, &InputObject::GetStateEnum>()
				),

				Function(
					"GetPosition",
					Overload(
						Const,
						Returns<const Vector3&>(),
						Argument<Enum::BoundDevice, Default(Enum::BoundDevice::Any)>("device")
					).Bind<InputObject, &InputObject::GetPosition>()
				),

				Function(
					"GetDelta",
					Overload(
						Const,
						Returns<const Vector3&>(),
						Argument<Enum::BoundDevice, Default(Enum::BoundDevice::Any)>("device")
					).Bind<InputObject, &InputObject::GetDelta>()
				),

				Function(
					"GetType",
					Overload(
						Const,
						Returns<Enum::InputType>()
					).Bind<InputObject, &InputObject::GetType>()
				),

				Function(
					"GetCode",
					Overload(
						Const,
						Returns<Enum::InputCode>()
					).Bind<InputObject, &InputObject::GetCode>()
				),

				Function(
					"GetDevice",
					Overload(
						Const,
						Returns<Enum::BoundDevice>()
					).Bind<InputObject, &InputObject::GetDevice>()
				)//,

				//Event(
				//	"Began",
				//	Argument<const std::shared_ptr<InputObject>&>("input")
				//).Bind<&InputObject::Began>(),
				//
				//Event(
				//	"Changed",
				//	Argument<const std::shared_ptr<InputObject>&>("input")
				//).Bind<&InputObject::Changed>(),
				//
				//Event(
				//	"Ended",
				//	Argument<const std::shared_ptr<InputObject>&>("input")
				//).Bind<&InputObject::Ended>()
			);
		}

		template <>
		void ReflectType<InputDevice>()
		{
			Reflect<InputDevice, InputObject>::Class
			(
				"InputDevice",
				{ "GameObject" },

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<InputBinding>()
		{
			Reflect<InputBinding, InputObject>::Class
			(
				"InputBinding",
				{ "GameObject" },

				Member<Bind(&InputBinding::BindingMode)>("BindingMode"),

				Constructor(
					Overload()
				),

				Function(
					"Bind",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<InputObject>&>("input")
					).Bind<InputBinding, &InputBinding::Bind>()
				),

				Function(
					"Unbind",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<InputObject>&>("input")
					).Bind<InputBinding, &InputBinding::Unbind>()
				),

				Function(
					"GetBindings",
					Overload(
						Const,
						Returns<int>()
					).Bind<InputBinding, &InputBinding::GetBindings>()
				),

				Function(
					"GetBinding",
					Overload(
						Const,
						Returns<std::shared_ptr<InputObject>>(),
						Argument<int>("index")
					).Bind<InputBinding, &InputBinding::GetBinding>()
				),

				Function(
					"IsBound",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::shared_ptr<InputObject>&>("input")
					).Bind<InputBinding, &InputBinding::IsBound>()
				)
			);
		}

		template <>
		void ReflectType<UserInput>()
		{
			Reflect<UserInput, Object>::Class
			(
				"UserInput",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"GetState",
					Overload(
						Mutable,
						Returns<bool>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetState>()
				),

				Function(
					"GetStateChanged",
					Overload(
						Mutable,
						Returns<bool>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetStateChanged>()
				),

				Function(
					"GetStateEnum",
					Overload(
						Mutable,
						Returns<Enum::InputState>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetStateEnum>()
				),

				Function(
					"GetPosition",
					Overload(
						Mutable,
						Returns<const Vector3&>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetPosition>()
				),

				Function(
					"GetDelta",
					Overload(
						Mutable,
						Returns<const Vector3&>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetDelta>()
				),

				Function(
					"GetType",
					Overload(
						Mutable,
						Returns<Enum::InputType>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetType>()
				),

				Function(
					"GetName",
					Overload(
						Mutable,
						Returns<const char*>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetName>()
				),

				Function(
					"GetInput",
					Overload(
						Mutable,
						Returns<std::shared_ptr<InputDevice>>(),
						Argument<Enum::InputCode>("code")
					).Bind<UserInput, &UserInput::GetInput>()
				)//,

				//Event(
				//	"Began",
				//	Argument<const std::shared_ptr<InputObject>&>("input")
				//).Bind<&InputObject::Began>(),
				//
				//Event(
				//	"Changed",
				//	Argument<const std::shared_ptr<InputObject>&>("input")
				//).Bind<&InputObject::Changed>(),
				//
				//Event(
				//	"Ended",
				//	Argument<const std::shared_ptr<InputObject>&>("input")
				//).Bind<&InputObject::Ended>()
			);
		}

		template <>
		void ReflectType<Enum::InputMode>()
		{
			Reflect<Enum::InputMode>::Enum
			(
				"InputMode",
				Value<Enum::InputMode::Or>("Or"),
				Value<Enum::InputMode::And>("And"),
				Value<Enum::InputMode::Xor>("Xor")
			);
		}
	}
}