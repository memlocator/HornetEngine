#include "Precision.h"

#include <cmath>

namespace std
{

	template <>
	Float min<float, double>(float a, double b)
	{
		return min<Float>((Float)a, (Float)b);
	}

	template <>
	Float min<double, float>(double a, float b)
	{
		return min<Float>((Float)a, (Float)b);
	}

	template <>
	Float max<float, double>(float a, double b)
	{
		return max<Float>((Float)a, (Float)b);
	}

	template <>
	Float max<double, float>(double a, float b)
	{
		return max<Float>((Float)a, (Float)b);
	}
}

template <typename T>
struct funcs;

template <>
struct funcs<float>
{
	static float sqrt(float x)
	{
		return sqrtf(x);
	}

	static float floor(float x)
	{
		return std::floorf(x);
	}

	static float ceil(float x)
	{
		return std::ceilf(x);
	}

	static float round(float x)
	{
		float floored = floor(x);

		if (x - floored < 0.5f)
			return floored;

		return ceil(x);
	}

	static float cos(float x)
	{
		return cosf(x);
	}

	static float sin(float x)
	{
		return sinf(x);
	}

	static float acos(float x)
	{
		return acosf(x);
	}

	static float asin(float x)
	{
		return asinf(x);
	}
};

template <>
struct funcs<double>
{
	static double sqrt(double x)
	{
		return ::sqrt(x);
	}

	static double floor(double x)
	{
		return std::floor(x);
	}

	static double ceil(double x)
	{
		return std::ceil(x);
	}

	static double round(double x)
	{
		double floored = floor(x);

		if (x - floored < 0.5f)
			return floored;

		return ceil(x);
	}

	static double cos(double x)
	{
		return cos(x);
	}

	static double sin(double x)
	{
		return sin(x);
	}

	static double acos(double x)
	{
		return acos(x);
	}

	static double asin(double x)
	{
		return asin(x);
	}
};

Float sqrtF(Float x)
{
	return funcs<Float>::sqrt(x);
}

Float floorF(Float x)
{
	return funcs<Float>::floor(x);
}

Float ceilF(Float x)
{
	return funcs<Float>::ceil(x);
}

Float roundF(Float x)
{
	return funcs<Float>::round(x);
}

Float cosF(Float x)
{
	return funcs<Float>::cos(x);
}

Float sinF(Float x)
{
	return funcs<Float>::sin(x);
}

Float acosF(Float x)
{
	return funcs<Float>::acos(x);
}

Float asinF(Float x)
{
	return funcs<Float>::asin(x);
}