#include "apple.h"

namespace app
{
	apple::apple() : m_location({ 0, 0 })
	{
		respawn();
	}

	void apple::respawn()
	{
		m_location.x = UNIT_SIZE * (rand() % (WIDTH / UNIT_SIZE));
		m_location.y = UNIT_SIZE * (rand() % (HEIGHT / UNIT_SIZE));
	}

	void apple::render()
	{
		renderer::set_color(1, 0, 0);
		renderer::quad(m_location.x, m_location.y, UNIT_SIZE, UNIT_SIZE);
	}
}