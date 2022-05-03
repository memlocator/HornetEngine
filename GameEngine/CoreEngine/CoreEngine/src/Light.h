#pragma once

import <vector>;

#include "Math/Vector3.h"
#include "Constants.h"
#include "Object.h"
#include "AabbTree.h"
#include "Dimensions.h"
#include "Math/Color4.h"

namespace GraphicsEngine
{
	class Camera;
	class FrameBuffer;

	class Light : public Engine::Object
	{
	public:
		struct LightTypeEnum
		{
			enum LightType
			{
				Directional,
				Point,
				Spot
			};
		};

		struct LightDirectionEnum
		{
			enum LightDirection
			{
				Right,
				Left,
				Top,
				Bottom,
				Front,
				Back
			};
		};

		typedef LightTypeEnum::LightType LightType;
		typedef LightDirectionEnum::LightDirection LightDirection;

		virtual ~Light() {}

		void Update(Float delta);

		bool ShadowDebugView = false;
		bool Enabled = true;
		Float Brightness = 1;
		Vector3 Attenuation;
		Vector3 Position;
		Vector3 Direction;
		Color4 Diffuse = 0xFFFFFFFF;
		Color4 Specular = 0xFFFFFFFF;
		Color4 Ambient = 0xFFFFFFFF;
		Float InnerRadius = PI / 5;
		Float OuterRadius = PI / 3;
		int SpotlightFalloff = 1;
		LightType Type = LightType::Directional;

		Float GetRadius() const { return ComputedRadius; }
		Float GetAttenuationOffset() const { return AttenuationOffset; }
		void RecomputeRadius();
		Dimensions GetShadowMapSize() const;
		void SetShadowsEnabled(bool enabled, int width = 128, int height = 128);
		bool AreShadowsEnabled() const;
		std::shared_ptr<FrameBuffer> GetShadowMap(LightDirection map) const;
		Aabb GetBoundingBox() const;
		Aabb ComputeSpotlightBoundingBox() const;
		const Matrix4& GetShadowMapTransformation() const;
		const Matrix4& GetShadowMapInverseTransformation() const;

		static Float ComputeRadius(Float a, Float b, Float c, Float value);

	private:
		bool ShadowsEnabled = false;
		Float ComputedRadius = 0;
		Float AttenuationOffset = 0;
		Matrix4 ShadowMapTransformation;
		Matrix4 ShadowMapInverseTransformation;

		std::weak_ptr<FrameBuffer> RightMap;
		std::weak_ptr<FrameBuffer> LeftMap;
		std::weak_ptr<FrameBuffer> TopMap;
		std::weak_ptr<FrameBuffer> BottomMap;
		std::weak_ptr<FrameBuffer> FrontMap;
		std::weak_ptr<FrameBuffer> BackMap;

		Dimensions ShadowMapSize;

		void GenBuffer(std::shared_ptr<FrameBuffer>& map, int width, int height);
		void DeleteBuffer(std::shared_ptr<FrameBuffer>& map);
	};
}

namespace Enum
{
	typedef GraphicsEngine::Light::LightType LightType;
	typedef GraphicsEngine::Light::LightDirection LightDirection;
}