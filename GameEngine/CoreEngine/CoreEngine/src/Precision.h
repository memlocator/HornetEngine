#pragma once

typedef double Float;
typedef int Int;

constexpr Float operator ""_F(long double x) { return (Float)x; }

namespace std
{
	template <typename T1, typename T2>
	Float max(T1, T2);
	
	template <>
	Float max<float, double>(float a, double b);

	template <>
	Float max<double, float>(double a, float b);

	template <typename T1, typename T2>
	Float min(T1, T2);

	template <>
	Float min<float, double>(float a, double b);

	template <>
	Float min<double, float>(double a, float b);
}