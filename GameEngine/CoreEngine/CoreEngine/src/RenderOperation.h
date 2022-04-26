#pragma once

#include "Object.h"

#include "IdentifierHeap.h"

namespace GraphicsEngine
{
	class RenderOperation : public Engine::Object
	{
	public:
		virtual ~RenderOperation();
		
		void Initialize();

		bool RenderAutomatically = false;

		virtual void Render() {};

		static void UpdateOperations(float delta);
		static void RenderOperations();

	private:
		typedef IDHeap<std::weak_ptr<RenderOperation>> OperationHeap;

		static OperationHeap& GetOperations();

		int OperationID = -1;
	};
}
