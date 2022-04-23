#pragma once

#include <type_traits>

namespace cmath
{
	template <typename T> requires std::is_floating_point_v<T>
	constexpr T abs(T x)
	{
		return (2 * (T)(x > 0) - 1) * x;
	}

	template <typename T>
	struct Unsigned;

	template <>
	struct Unsigned<bool>
	{
		typedef bool Type;
	};

	template <>
	struct Unsigned<unsigned char>
	{
		typedef unsigned char Type;
	};

	template <>
	struct Unsigned<signed char>
	{
		typedef unsigned char Type;
	};

	template <>
	struct Unsigned<unsigned short>
	{
		typedef unsigned short Type;
	};

	template <>
	struct Unsigned<short>
	{
		typedef unsigned short Type;
	};

	template <>
	struct Unsigned<unsigned int>
	{
		typedef unsigned int Type;
	};

	template <>
	struct Unsigned<int>
	{
		typedef unsigned int Type;
	};

	template <>
	struct Unsigned<unsigned long long>
	{
		typedef unsigned long long Type;
	};

	template <>
	struct Unsigned<long long>
	{
		typedef unsigned long long Type;
	};

	template <typename T> requires std::is_integral_v<T>
	constexpr T abs(T x)
	{
		typedef typename Unsigned<T>::Type UnsignedType;

		return (x < 0) ? (0 - (UnsignedType)x) : (UnsignedType)x;
	}

	template <typename T>
	constexpr T min(T a, T b)
	{
		return a > b ? b : a;
	}

	template <typename T>
	constexpr T max(T a, T b)
	{
		return a < b ? b : a;
	}
}