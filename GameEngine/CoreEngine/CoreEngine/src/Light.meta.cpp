#include "Light.h"

#include "FrameBuffer.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Light>()
		{
			Reflect<Light, Object>::Class
			(
				"Light",
				{ "GameObject" },

				Member<Bind(&Light::ShadowDebugView)>("ShadowDebugView"),
				Member<Bind(&Light::Enabled)>("Enabled"),
				Member<Bind(&Light::Brightness)>("Brightness"),
				Member<Bind(&Light::Attenuation)>("Attenuation"),
				Member<Bind(&Light::Position)>("Position"),
				Member<Bind(&Light::Direction)>("Direction"),
				Member<Bind(&Light::Diffuse)>("Diffuse"),
				Member<Bind(&Light::Specular)>("Specular"),
				Member<Bind(&Light::Ambient)>("Ambient"),
				Member<Bind(&Light::InnerRadius)>("InnerRadius"),
				Member<Bind(&Light::OuterRadius)>("OuterRadius"),
				Member<Bind(&Light::SpotlightFalloff)>("SpotlightFalloff"),
				Member<Bind(&Light::Type)>("Type"),

				Constructor(
					Overload()
				),

				Function(
					"GetRadius",
					Overload(
						Const,
						Returns<Float>()
					).Bind<Light, &Light::GetRadius>()
				),

				Function(
					"GetAttenuationOffset",
					Overload(
						Const,
						Returns<Float>()
					).Bind<Light, &Light::GetAttenuationOffset>()
				),

				Function(
					"RecomputeRadius",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Light, &Light::RecomputeRadius>()
				),

				Function(
					"GetShadowMapSize",
					Overload(
						Const,
						Returns<Dimensions>()
					).Bind<Light, &Light::GetShadowMapSize>()
				),

				Function(
					"SetShadowsEnabled",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("enabled"),
						Argument<int, Default(128)>("width"),
						Argument<int, Default(128)>("height")
					).Bind<Light, &Light::SetShadowsEnabled>()
				),

				Function(
					"AreShadowsEnabled",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Light, &Light::AreShadowsEnabled>()
				),

				Function(
					"GetShadowMap",
					Overload(
						Const,
						Returns<std::shared_ptr<FrameBuffer>>(),
						Argument<Enum::LightDirection>("map")
					).Bind<Light, &Light::GetShadowMap>()
				),

				Function(
					"GetBoundingBox",
					Overload(
						Const,
						Returns<Aabb>()
					).Bind<Light, &Light::GetBoundingBox>()
				),

				Function(
					"ComputeSpotlightBoundingBox",
					Overload(
						Const,
						Returns<Aabb>()
					).Bind<Light, &Light::ComputeSpotlightBoundingBox>()
				),

				Function(
					"GetShadowMapTransformation",
					Overload(
						Const,
						Returns<const Matrix3&>()
					).Bind<Light, &Light::GetShadowMapTransformation>()
				),

				Function(
					"GetShadowMapInverseTransformation",
					Overload(
						Const,
						Returns<const Matrix3&>()
					).Bind<Light, &Light::GetShadowMapInverseTransformation>()
				),

				Function(
					"ComputeRadius",
					Overload(
						Static,
						Returns<Float>(),
						Argument<Float>("a"),
						Argument<Float>("b"),
						Argument<Float>("c"),
						Argument<Float>("value")
					).Bind<&Light::ComputeRadius>()
				)
			);
		}

		template <>
		void ReflectType<Enum::LightType>()
		{
			Reflect<Enum::LightType>::Enum
			(
				"LightType",
				Value<Enum::LightType::Directional>("Directional"),
				Value<Enum::LightType::Point>("Point"),
				Value<Enum::LightType::Spot>("Spot")
			);
		}

		template <>
		void ReflectType<Enum::LightDirection>()
		{
			Reflect<Enum::LightDirection>::Enum
			(
				"LightDirection",
				Value<Enum::LightDirection::Right>("Right"),
				Value<Enum::LightDirection::Left>("Left"),
				Value<Enum::LightDirection::Top>("Top"),
				Value<Enum::LightDirection::Bottom>("Bottom"),
				Value<Enum::LightDirection::Front>("Front"),
				Value<Enum::LightDirection::Back>("Back")
			);
		}
	}
}