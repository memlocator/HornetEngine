#include "EnginePackage.h"

#include "Object.h"
#include "Vector3.h"
#include "Vector3S.h"
#include "Vector2.h"
#include "Vector2S.h"
#include "Color1.h"
#include "Color1I.h"
#include "Color2.h"
#include "Color2I.h"
#include "Color3.h"
#include "Color3I.h"
#include "Color4.h"
#include "Color4I.h"
#include "Ray.h"
#include "PointGenerator.h"
#include "Quaternion.h"
#include "OBB.h"
#include "Matrix4.h"
#include "Matrix3.h"
#include "DeviceVector.h"
#include "BoundingSphere.h"
#include "Aabb.h"
#include "Environment.h"
#include "Environments.h"
#include "GameEngine.h"
#include "Simulation.h"
#include "Transform.h"
#include "LuaInput.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<Object>();

		template <>
		extern void ReflectType<Vector3>();

		template <>
		extern void ReflectType<Vector3S>();

		template <>
		extern void ReflectType<Vector2>();

		template <>
		extern void ReflectType<Vector2S>();

		template <>
		extern void ReflectType<Color1>();

		template <>
		extern void ReflectType<Color1I>();

		template <>
		extern void ReflectType<Color2>();

		template <>
		extern void ReflectType<Color2I>();

		template <>
		extern void ReflectType<Color3>();

		template <>
		extern void ReflectType<Color3I>();

		template <>
		extern void ReflectType<Color4>();

		template <>
		extern void ReflectType<Color4I>();

		template <>
		extern void ReflectType<Ray>();

		template <>
		extern void ReflectType<Quaternion>();

		template <>
		extern void ReflectType<VectorGenerator>();

		template <>
		extern void ReflectType<NumberRange>();

		template <>
		extern void ReflectType<PointGenerator>();

		template <>
		extern void ReflectType<UnitVectorGenerator>();

		template <>
		extern void ReflectType<ConeUnitVectorGenerator>();

		template <>
		extern void ReflectType<OBB>();

		template <>
		extern void ReflectType<Matrix4>();

		template <>
		extern void ReflectType<Matrix3>();

		template <>
		extern void ReflectType<DeviceVector>();

		template <>
		extern void ReflectType<DeviceAxis>();

		template <>
		extern void ReflectType<BoundingSphere>();

		template <>
		extern void ReflectType<Aabb>();

		template <>
		extern void ReflectType<Environment>();

		template <>
		extern void ReflectType<Environments>();

		template <>
		extern void ReflectType<GameEngine>();

		template <>
		extern void ReflectType<ProcessArguments>();

		template <>
		extern void ReflectType<Simulation>();

		template <>
		extern void ReflectType<Transform>();

		template <>
		extern void ReflectType<InputObject>();

		template <>
		extern void ReflectType<InputDevice>();

		template <>
		extern void ReflectType<InputBinding>();

		template <>
		extern void ReflectType<UserInput>();

		template <>
		extern void ReflectType<Enum::InputMode>();

		template <>
		extern void ReflectType<Enum::InputCode>();

		template <>
		extern void ReflectType<Enum::InputType>();

		template <>
		extern void ReflectType<Enum::InputState>();

		template <>
		extern void ReflectType<Enum::BoundDevice>();

		void InitializeFundamentalTypes()
		{
			Reflect<void>::FundamentalType("void");

			Reflect<bool>::FundamentalType("bool");
			Reflect<char>::FundamentalType<lua_Number, lua_Integer>("char");
			Reflect<signed char>::FundamentalType<lua_Number, lua_Integer>("signed char");
			Reflect<unsigned char>::FundamentalType<lua_Number, lua_Integer>("unsigned char");
			Reflect<short>::FundamentalType<lua_Number, lua_Integer>("short");
			Reflect<unsigned short>::FundamentalType<lua_Number, lua_Integer>("unsigned short");
			Reflect<int>::FundamentalType<lua_Number, lua_Integer>("int");
			Reflect<unsigned int>::FundamentalType<lua_Number, lua_Integer>("unsigned int");
			Reflect<long long>::FundamentalType<lua_Number, lua_Integer>("long long");
			Reflect<unsigned long long>::FundamentalType<lua_Number, lua_Integer>("unsigned long long");

			Reflect<float>::FundamentalType<lua_Number, lua_Integer>("float");
			Reflect<double>::FundamentalType<lua_Number, lua_Integer>("double");

			Reflect<std::string>::FundamentalType("string");
		}

		template <>
		void ReflectPackage<EnginePackage>()
		{
			ReflectFromPackage<
				Object,
				Vector3,
				Vector3S,
				Vector2,
				Vector2S,
				Color1,
				Color1I,
				Color2,
				Color2I,
				Color3,
				Color3I,
				Color4,
				Color4I,
				Ray,
				Quaternion,
				VectorGenerator,
				NumberRange,
				PointGenerator,
				UnitVectorGenerator,
				ConeUnitVectorGenerator,
				OBB,
				Matrix4,
				Matrix3,
				DeviceVector,
				DeviceAxis,
				BoundingSphere,
				Aabb,
				Environment,
				Environments,
				GameEngine,
				ProcessArguments,
				Simulation,
				Transform,
				InputObject,
				InputDevice,
				InputBinding,
				UserInput,
				Enum::InputMode,
				Enum::InputCode,
				Enum::InputType,
				Enum::InputState,
				Enum::BoundDevice
			>();
			InitializeFundamentalTypes();
		}
	}
}