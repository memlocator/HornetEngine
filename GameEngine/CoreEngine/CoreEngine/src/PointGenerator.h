#pragma once

#include "Vector3.h"
#include "Constants.h"

#include <cmath>

class VectorGenerator
{
public:
	virtual Vector3 Generate() {
		return Vector3();
	}

	static Float randf()
	{
		return Float(rand()) / RAND_MAX;
	}
};

struct NumberRange
{
	Float Min;
	Float Max;

	Float rand()
	{
		return Min + VectorGenerator::randf() * (Max - Min);
	}

	void Set(Float min, Float max)
	{
		Min = min;
		Max = max;
	}

	NumberRange() : Min(0), Max(1) {}
	NumberRange(Float min) : Min(min), Max(min) {}
	NumberRange(Float min, Float max) : Min(min), Max(max) {}
	NumberRange(const NumberRange& range) : Min(range.Min), Max(range.Max) {}

	NumberRange& operator=(Float value)
	{
		Min = value;
		Max = value;
	}
};

class PointGenerator : public VectorGenerator
{
public:
	Vector3 Position;

	PointGenerator(const Vector3& position = Vector3()) : Position(position) {}

	Vector3 Generate()
	{
		return Position;
	}
};

class UnitVectorGenerator : public VectorGenerator
{
public:
	Vector3 Generate()
	{
		Float theta = 2 * PI * randf();
		Float phi = std::acos(1 - 2 * randf());
		Float sinPhi = std::sin(phi);

		return Vector3(sinPhi * std::cos(theta), sinPhi * std::sin(theta), std::cos(phi));
	}
};

class ConeUnitVectorGenerator : public VectorGenerator
{
public:
	Vector3 Normal = Vector3(0, 1, 0);
	NumberRange Angle;

	Vector3 Generate()
	{
		Float ratio = (1 - Normal.Y) * (Normal.X * Normal.X + Normal.Z * Normal.Z);
		Float shared = -ratio * Normal.X * Normal.Z;
		Vector3 vector1(shared, Normal.Z, ratio * Normal.X * Normal.X + Normal.Y);
		Vector3 vector2(ratio * Normal.Z * Normal.Z + Normal.Y, Normal.Z, shared);

		Float theta = NumberRange(0, 2 * PI).rand();

		Vector3 direction = std::cos(theta) * vector1 + std::sin(theta) * vector2;

		Float rangeStart = Angle.Min / Angle.Max;

		Float theta2 = Angle.Min + (Angle.Max - Angle.Min) * std::acos(rangeStart + VectorGenerator::randf() * (1 - rangeStart)) * 2 / PI;

		return (std::cos(theta2) * Normal + std::sin(theta2) * direction);
	}
};
