#pragma once

#include "point.h"
#include "renderer.h"
#include "direction.h"
#include <list>

namespace app
{
	class snake
	{
	public:
		snake(int starting_size);
		void update();
		void render() const;
		void set_direction(const app::direction& direction);
		void inc_size_by_one();
		bool check_if_snake_eat_himself() const;
		inline point get_head() const { return m_body.front(); }
		inline direction get_direction() const { return m_direction; }
		
	private:
		std::list<point> m_body;
		app::direction m_direction;
	};
}