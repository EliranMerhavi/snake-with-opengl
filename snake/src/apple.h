#pragma once
#include "renderer.h"
#include "point.h"

namespace app
{
	class apple
	{
	public:
		apple();
		void respawn();
		void render();
		inline point get_location() const { return m_location; }
	private:
		point m_location;
	};
}


