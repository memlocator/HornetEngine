#include "Object.h"

#include "Reflection/Reflection.h"

/*
#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Object>()
		{
			Reflect<Object>::Class
			(
				"Object",
				{ "GameObject" }
			);
		}
	}
}
*/

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Object>()
		{
			Reflect<Object>::Class
			(
				"Object",
				{ "GameObject" },

				Member<Bind(&Object::Name)>("Name"),
				Member<Bind(&Object::SiblingComponents)>("SiblingComponents"),
				Member<Bind(&Object::ParentComponent)>("ParentComponent"),
				Member<Bind(&Object::AncestorComponents)>("AncestorComponents"),
				Member<Bind(&Object::SuperComponentHeight)>("SuperComponentHeight"),

				Property(
					"Parent",
					Getter<std::shared_ptr<Object>>(Const).Bind<Object, &Object::GetParent>(),
					Setter<const std::shared_ptr<Object>&>(Mutable).Bind<Object, &Object::SetParent>()
				),

				Function(
					"Update",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<float>("delta")
					).Bind<Object, &Object::Update>()
				),

				Function(
					"GetObjectID",
					Overload(
						Const,
						Returns<int>()
					).Bind<Object, &Object::GetObjectID>()
				),

				Function(
					"GetTypeName",
					Overload(
						Const,
						Returns<const std::string&>()
					).Bind<Object, &Object::GetTypeName>()
				),

				Function(
					"IsA",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::string&>("name"),
						Argument<bool, true>("inherits")
					).Bind<Object, &Object::IsA>()
				),

				Function(
					"HasRequirements",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Object, &Object::HasRequirements>()
				),

				Function(
					"GetFullName",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Object, &Object::GetFullName>()
				),

				Function(
					"GetChildren",
					Overload(
						Const,
						Returns<int>()
					).Bind<Object, &Object::GetChildren>()
				),

				Function(
					"Get",
					Overload(
						Mutable,
						Returns<std::shared_ptr<Object>>(),
						Argument<int>("index")
					).Bind<Object, &Object::Get>(),
					Overload(
						Mutable,
						Returns<std::shared_ptr<Object>>(),
						Argument<const std::string&>("className"),
						Argument<bool, true>("inherited")
					).Bind<Object, &Object::Get>()
				),

				Function(
					"GetByName",
					Overload(
						Mutable,
						Returns<std::shared_ptr<Object>>(),
						Argument<const std::string&>("name")
					).Bind<Object, &Object::GetByName>()
				),

				Function(
					"HasA",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::string&>("className"),
						Argument<bool, true>("inherits")
					).Bind<Object, &Object::HasA>()
				),

				Function(
					"Remove",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Object, &Object::Remove>()
				),

				Function(
					"GetComponent",
					Overload(
						Const,
						Returns<std::shared_ptr<Object>>(),
						Argument<const std::string&>("className"),
						Argument<bool, true>("inherits")
					).Bind<Object, &Object::GetComponent>()
				),

				Function(
					"CheckRestriction",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::shared_ptr<Object>&>("object")
					).Bind<Object, &Object::CheckRestriction>()
				),

				Function(
					"CheckRequirements",
					Overload(
						Const,
						Returns<const std::string&>(),
						Argument<const std::shared_ptr<Object>&>("object")
					).Bind<Object, &Object::CheckRequirements>()
				),

				Function(
					"IsAncestorOf",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::shared_ptr<Object>&>("object")
					).Bind<Object, &Object::IsAncestorOf>()
				),

				Function(
					"IsDescendantOf",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::shared_ptr<Object>&>("object")
					).Bind<Object, &Object::IsDescendantOf>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Object, &Object::operator std::string>()
				)
			);
		}
	}
}