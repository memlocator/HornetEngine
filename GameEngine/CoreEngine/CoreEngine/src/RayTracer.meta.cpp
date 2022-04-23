#include "RayTracer.h"

#include "Scene.h"
#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<RayTracer>()
		{
			Reflect<RayTracer, Object>::Class
			(
				"RayTracer",
				{ "GameObject" },

				Member<Bind(&RayTracer::BatchWidth)>("BatchWidth"),
				Member<Bind(&RayTracer::BatchHeight)>("BatchHeight"),
				Member<Bind(&RayTracer::MaxBounces)>("MaxBounces"),
				Member<Bind(&RayTracer::Samples)>("Samples"),
				Member<Bind(&RayTracer::CurrentScene)>("CurrentScene"),

				Function(
					"SetMaxThreads",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("maxThreads")
					).Bind<RayTracer, &RayTracer::SetMaxThreads>()
				),

				Function(
					"GetMaxThreads",
					Overload(
						Const,
						Returns<int>()
					).Bind<RayTracer, &RayTracer::GetMaxThreads>()
				),

				Function(
					"GetHardwareThreads",
					Overload(
						Const,
						Returns<int>()
					).Bind<RayTracer, &RayTracer::GetHardwareThreads>()
				),

				Function(
					"Configure",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height")
					).Bind<RayTracer, &RayTracer::Configure>()
				),

				Function(
					"SetViewport",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("minX"),
						Argument<int>("minY"),
						Argument<int>("maxX"),
						Argument<int>("maxY")
					).Bind<RayTracer, &RayTracer::SetViewport>()
				),

				Function(
					"Render",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<RayTracer, &RayTracer::Render>()
				),

				Function(
					"DrawTo",
					Overload(
						Const,
						Returns<void>(),
						Argument<const std::shared_ptr<Texture>&>("texture")
					).Bind<RayTracer, &RayTracer::DrawTo>()
				),

				Function(
					"Save",
					Overload(
						Const,
						Returns<void>(),
						Argument<const std::string&>("filePath")
					).Bind<RayTracer, &RayTracer::Save>()
				)
			);
		}
	}
}