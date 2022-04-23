#include "LuaInput.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::InputCode>()
		{
			Reflect<Enum::InputCode>::Enum
			(
				"InputCode",

				Value<Enum::InputCode::MouseLeft>("MouseLeft"),
				Value<Enum::InputCode::MouseRight>("MouseRight"),
				Value<Enum::InputCode::MouseMiddle>("MouseMiddle"),
				Value<Enum::InputCode::MouseWheel>("MouseWheel"),
				Value<Enum::InputCode::MousePosition>("MousePosition"),

				Value<Enum::InputCode::NumpadZero>("NumpadZero"),
				Value<Enum::InputCode::NumpadOne>("NumpadOne"),
				Value<Enum::InputCode::NumpadTwo>("NumpadTwo"),
				Value<Enum::InputCode::NumpadThree>("NumpadThree"),
				Value<Enum::InputCode::NumpadFour>("NumpadFour"),
				Value<Enum::InputCode::NumpadFive>("NumpadFive"),
				Value<Enum::InputCode::NumpadSix>("NumpadSix"),
				Value<Enum::InputCode::NumpadSeven>("NumpadSeven"),
				Value<Enum::InputCode::NumpadEight>("NumpadEight"),
				Value<Enum::InputCode::NumpadNine>("NumpadNine"),

				Value<Enum::InputCode::NumpadSlash>("NumpadSlash"),
				Value<Enum::InputCode::NumpadAstrisk>("NumpadAstrisk"),
				Value<Enum::InputCode::NumpadHyphen>("NumpadHyphen"),
				Value<Enum::InputCode::NumpadPlus>("NumpadPlus"),
				Value<Enum::InputCode::NumpadEnter>("NumpadEnter"),
				Value<Enum::InputCode::NumpadPeriod>("NumpadPeriod"),

				Value<Enum::InputCode::BracketOpen>("BracketOpen"),
				Value<Enum::InputCode::BracketClose>("BracketClose"),
				Value<Enum::InputCode::Backslash>("Backslash"),
				Value<Enum::InputCode::Semicolon>("Semicolon"),
				Value<Enum::InputCode::Apostrophe>("Apostrophe"),
				Value<Enum::InputCode::Comma>("Comma"),
				Value<Enum::InputCode::Period>("Period"),
				Value<Enum::InputCode::Slash>("Slash"),
				Value<Enum::InputCode::GraveAccent>("GraveAccent"),
				Value<Enum::InputCode::Hyphen>("Hyphen"),
				Value<Enum::InputCode::Equals>("Equals"),

				Value<Enum::InputCode::Space>("Space"),

				Value<Enum::InputCode::F1>("F1"),
				Value<Enum::InputCode::F2>("F2"),
				Value<Enum::InputCode::F3>("F3"),
				Value<Enum::InputCode::F4>("F4"),
				Value<Enum::InputCode::F5>("F5"),
				Value<Enum::InputCode::F6>("F6"),
				Value<Enum::InputCode::F7>("F7"),
				Value<Enum::InputCode::F8>("F8"),
				Value<Enum::InputCode::F9>("F9"),
				Value<Enum::InputCode::F10>("F10"),
				Value<Enum::InputCode::F11>("F11"),
				Value<Enum::InputCode::F12>("F12"),

				Value<Enum::InputCode::Zero>("Zero"),
				Value<Enum::InputCode::One>("One"),
				Value<Enum::InputCode::Two>("Two"),
				Value<Enum::InputCode::Three>("Three"),
				Value<Enum::InputCode::Four>("Four"),
				Value<Enum::InputCode::Five>("Five"),
				Value<Enum::InputCode::Six>("Six"),
				Value<Enum::InputCode::Seven>("Seven"),
				Value<Enum::InputCode::Eight>("Eight"),
				Value<Enum::InputCode::Nine>("Nine"),

				Value<Enum::InputCode::Escape>("Escape"),
				Value<Enum::InputCode::Tab>("Tab"),
				Value<Enum::InputCode::CapsLock>("CapsLock"),
				Value<Enum::InputCode::LeftShift>("LeftShift"),
				Value<Enum::InputCode::RightShift>("RightShift"),
				Value<Enum::InputCode::LeftControl>("LeftControl"),
				Value<Enum::InputCode::RightControl>("RightControl"),
				Value<Enum::InputCode::LeftAlt>("LeftAlt"),
				Value<Enum::InputCode::RightAlt>("RightAlt"),
				Value<Enum::InputCode::Enter>("Enter"),
				Value<Enum::InputCode::Backspace>("Backspace"),
				Value<Enum::InputCode::Insert>("Insert"),
				Value<Enum::InputCode::DeleteButton>("DeleteButton"),
				Value<Enum::InputCode::Home>("Home"),
				Value<Enum::InputCode::End>("End"),
				Value<Enum::InputCode::PageUp>("PageUp"),
				Value<Enum::InputCode::PageDown>("PageDown"),
				Value<Enum::InputCode::NumLock>("NumLock"),

				Value<Enum::InputCode::UpArrow>("UpArrow"),
				Value<Enum::InputCode::DownArrow>("DownArrow"),
				Value<Enum::InputCode::LeftArrow>("LeftArrow"),
				Value<Enum::InputCode::RightArrow>("RightArrow"),

				Value<Enum::InputCode::A>("A"),
				Value<Enum::InputCode::B>("B"),
				Value<Enum::InputCode::C>("C"),
				Value<Enum::InputCode::D>("D"),
				Value<Enum::InputCode::E>("E"),
				Value<Enum::InputCode::F>("F"),
				Value<Enum::InputCode::G>("G"),
				Value<Enum::InputCode::H>("H"),
				Value<Enum::InputCode::I>("I"),
				Value<Enum::InputCode::J>("J"),
				Value<Enum::InputCode::K>("K"),
				Value<Enum::InputCode::L>("L"),
				Value<Enum::InputCode::M>("M"),
				Value<Enum::InputCode::N>("N"),
				Value<Enum::InputCode::O>("O"),
				Value<Enum::InputCode::P>("P"),
				Value<Enum::InputCode::Q>("Q"),
				Value<Enum::InputCode::R>("R"),
				Value<Enum::InputCode::S>("S"),
				Value<Enum::InputCode::T>("T"),
				Value<Enum::InputCode::U>("U"),
				Value<Enum::InputCode::V>("V"),
				Value<Enum::InputCode::W>("W"),
				Value<Enum::InputCode::X>("X"),
				Value<Enum::InputCode::Y>("Y"),
				Value<Enum::InputCode::Z>("Z"),

				Value<Enum::InputCode::Codes>("Codes")
			);
		}

		template <>
		void ReflectType<Enum::InputType>()
		{
			Reflect<Enum::InputType>::Enum
			(
				"InputType",
				Value<Enum::InputType::Button>("Button"),
				Value<Enum::InputType::Point>("Point")
			);
		}

		template <>
		void ReflectType<Enum::InputState>()
		{
			Reflect<Enum::InputState>::Enum
			(
				"InputState",
				Value<Enum::InputState::Began>("Began"),
				Value<Enum::InputState::Changed>("Changed"),
				Value<Enum::InputState::Ended>("Ended"),

				Value<Enum::InputState::Idle>("Idle"),
				Value<Enum::InputState::Active>("Active"),

				Value<Enum::InputState::None>("None")
			);
		}

		template <>
		void ReflectType<Enum::BoundDevice>()
		{
			Reflect<Enum::BoundDevice>::Enum
			(
				"BoundDevice",
				Value<Enum::BoundDevice::Any>("Any"),
				Value<Enum::BoundDevice::Mouse1>("Mouse1"),
				Value<Enum::BoundDevice::Input1>("Input1")
			);
		}
	}
}