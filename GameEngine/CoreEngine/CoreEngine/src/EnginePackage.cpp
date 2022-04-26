#include "EnginePackage.h"

#include "Object.h"
#include "Vector3.h"
#include "RGBA.h"
#include "Ray.h"
#include "PointGenerator.h"
#include "Quaternion.h"
#include "OBB.h"
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
		extern void ReflectType<RGBA>();

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
				RGBA,
				Ray,
				Quaternion,
				VectorGenerator,
				NumberRange,
				PointGenerator,
				UnitVectorGenerator,
				ConeUnitVectorGenerator,
				OBB,
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