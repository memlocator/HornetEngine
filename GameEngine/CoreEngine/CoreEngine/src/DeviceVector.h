#pragma once

#include "Vector3.h"

class DeviceAxis
{
public:
	Float Scale;
	Float Offset;

	constexpr DeviceAxis(Float scale = 0, Float offset = 0) : Scale(scale), Offset(offset) {}

	void Set(Float newScale, Float newOffset);
	Float Calculate(Float base, Float size) const;

	bool operator==(const DeviceAxis& other) const;
	bool operator!=(const DeviceAxis& other) const;
	DeviceAxis operator+(const DeviceAxis& axis) const;
	DeviceAxis operator-(const DeviceAxis& axis) const;
	DeviceAxis operator-() const;
	DeviceAxis operator*(Float scalar) const;
	DeviceAxis operator/(Float scalar) const;
	DeviceAxis& operator+=(const DeviceAxis& axis);
	DeviceAxis& operator-=(const DeviceAxis& axis);
	DeviceAxis& operator*=(Float scalar);
	DeviceAxis& operator/=(Float scalar);
};

DeviceAxis operator*(Float scalar, DeviceAxis axis);

class DeviceVector
{
public:
	DeviceAxis X;
	DeviceAxis Y;

	constexpr DeviceVector(Float xScale = 0, Float xOffset = 0, Float yScale = 0, Float yOffset = 0) : X(xScale, xOffset), Y(yScale, yOffset) {}
	constexpr DeviceVector(const DeviceAxis& x, const DeviceAxis& y) : X(x), Y(y) {}

	void Set(Float xScale, Float xOffset, Float yScale, Float yOffset);
	void Set(const DeviceAxis& xAxis, const DeviceAxis& yAxis);
	Vector3 Calculate(const Vector3& base, const Vector3& size) const;
	Vector3 Calculate(Float baseX, Float baseY, Float sizeX, Float sizeY) const;
	DeviceVector Lerp(Float t, const DeviceVector& goal) const;

	bool operator==(const DeviceVector& other) const;
	bool operator!=(const DeviceVector& other) const;
	DeviceVector operator+(const DeviceVector& vector) const;
	DeviceVector operator-(const DeviceVector& vector) const;
	DeviceVector operator-() const;
	DeviceVector operator*(Float scalar) const;
	DeviceVector operator/(Float scalar) const;
	DeviceVector& operator+=(const DeviceVector& vector);
	DeviceVector& operator-=(const DeviceVector& vector);
	DeviceVector& operator*=(Float scalar);
	DeviceVector& operator/=(Float scalar);
};

DeviceVector operator*(Float scalar, const DeviceVector& vector);

std::ostream& operator<<(std::ostream& out, const DeviceAxis& axis);

std::ostream& operator<<(std::ostream& out, const DeviceVector& vector);
