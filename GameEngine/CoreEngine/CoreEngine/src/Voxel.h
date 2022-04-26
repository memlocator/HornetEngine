#pragma once

#include "Object.h"
#include "Coordinates.h"

namespace Engine
{
	class Voxel : public Object
	{
	public:
		void SetPosition(const Coordinates& position);
		Coordinates GetPosition() const;

		virtual void Removed() {}

	protected:
		virtual void PositionChanged(const Coordinates& oldPosition, const Coordinates& newPosition) {}

	private:
		Coordinates Position;
	};
}