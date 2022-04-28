#include "DeviceVector.h"

#include <iostream>

void DeviceAxis::Set(Float newScale, Float newOffset)
{
	Scale = newScale;
	Offset = newOffset;
}

Float DeviceAxis::Calculate(Float base, Float size) const
{
	return base + Offset + Scale * size;
}

bool DeviceAxis::operator==(const DeviceAxis& other) const
{
	return Scale == other.Scale && Offset == other.Offset;
}

bool DeviceAxis::operator!=(const DeviceAxis& other) const
{
	return Scale != other.Scale || Offset != other.Offset;
}

DeviceAxis DeviceAxis::operator+(const DeviceAxis& axis) const
{
	return DeviceAxis(Scale + axis.Scale, Offset + axis.Offset);
}

DeviceAxis DeviceAxis::operator-(const DeviceAxis& axis) const
{
	return DeviceAxis(Scale - axis.Scale, Offset - axis.Offset);
}

DeviceAxis DeviceAxis::operator-() const
{
	return DeviceAxis(-Scale, -Offset);
}

DeviceAxis DeviceAxis::operator*(Float scalar) const
{
	return DeviceAxis(scalar * Scale, scalar * Offset);
}

DeviceAxis DeviceAxis::operator/(Float scalar) const
{
	return DeviceAxis(Scale / scalar, Offset / scalar);
}

DeviceAxis& DeviceAxis::operator+=(const DeviceAxis& axis)
{
	Scale += axis.Scale;
	Offset += axis.Offset;

	return *this;
}

DeviceAxis& DeviceAxis::operator-=(const DeviceAxis& axis)
{
	Scale -= axis.Scale;
	Offset -= axis.Offset;

	return *this;
}

DeviceAxis& DeviceAxis::operator*=(Float scalar)
{
	Scale *= scalar;
	Offset *= scalar;

	return *this;
}

DeviceAxis& DeviceAxis::operator/=(Float scalar)
{
	Scale /= scalar;
	Offset /= scalar;

	return *this;
}

DeviceAxis operator*(Float scalar, DeviceAxis axis)
{
	return DeviceAxis(scalar * axis.Scale, scalar * axis.Offset);
}

bool DeviceVector::operator==(const DeviceVector& other) const
{
	return X == other.X && Y == other.Y;
}

bool DeviceVector::operator!=(const DeviceVector& other) const
{
	return X != other.X || Y != other.Y;
}

void DeviceVector::Set(Float xScale, Float xOffset, Float yScale, Float yOffset)
{
	X.Set(xScale, xOffset);
	Y.Set(yScale, yOffset);
}

void DeviceVector::Set(const DeviceAxis& xAxis, const DeviceAxis& yAxis)
{
	X = xAxis;
	Y = yAxis;
}

Vector3 DeviceVector::Calculate(const Vector3& base, const Vector3& size) const
{
	return Calculate(base.X, base.Y, size.X, size.Y);
}

Vector3 DeviceVector::Calculate(Float baseX, Float baseY, Float sizeX, Float sizeY) const
{
	return Vector3(X.Calculate(baseX, sizeX), Y.Calculate(baseY, sizeY));
}

DeviceVector DeviceVector::Lerp(Float t, const DeviceVector& goal) const
{
	return (1 - t) * *this + t * goal;
}

DeviceVector DeviceVector::operator+(const DeviceVector& vector) const
{
	return DeviceVector(X + vector.X, Y + vector.Y);
}

DeviceVector DeviceVector::operator-(const DeviceVector& vector) const
{
	return DeviceVector(X - vector.X, Y - vector.Y);
}

DeviceVector DeviceVector::operator-() const
{
	return DeviceVector(-X, -Y);
}

DeviceVector DeviceVector::operator*(Float scalar) const
{
	return DeviceVector(scalar * X, scalar * Y);
}

DeviceVector DeviceVector::operator/(Float scalar) const
{
	return DeviceVector(X / scalar, Y / scalar);
}

DeviceVector& DeviceVector::operator+=(const DeviceVector& vector)
{
	X += vector.X;
	Y += vector.Y;

	return *this;
}

DeviceVector& DeviceVector::operator-=(const DeviceVector& vector)
{
	X -= vector.X;
	Y -= vector.Y;

	return *this;
}

DeviceVector& DeviceVector::operator*=(Float scalar)
{
	X *= scalar;
	Y *= scalar;

	return *this;
}

DeviceVector& DeviceVector::operator/=(Float scalar)
{
	X /= scalar;
	Y /= scalar;

	return *this;
}

DeviceVector operator*(Float scalar, const DeviceVector& vector)
{
	return DeviceVector(scalar * vector.X, scalar * vector.Y);
}

std::ostream& operator<<(std::ostream& out, const DeviceAxis& axis)
{
	out << "[ " << (axis.Scale * 100) << "%, " << axis.Offset << " ]";

	return out;
}

std::ostream& operator<<(std::ostream& out, const DeviceVector& vector)
{
	out << "{ " << vector.X << ", " << vector.Y << " }";

	return out;
}
