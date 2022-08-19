#include "snake.h"

namespace app
{
	snake::snake(int starting_size) : m_body(), m_direction(app::direction::RIGHT)
	{
		m_body.push_back({ 0, 0 });

		for (int i = 0; i < starting_size - 1; i++)
		{
			inc_size_by_one();
		}
	}

	void snake::update()
	{
		inc_size_by_one();
		m_body.pop_back();
	}

	void snake::render() const
	{
		renderer::set_color(0, 1, 0);
		for (auto part : m_body)
		{
			renderer::quad(part.x, part.y, UNIT_SIZE, UNIT_SIZE);
		}
	}

	void snake::set_direction(const app::direction& direction)
	{
		m_direction = direction;
	}

	void snake::inc_size_by_one()
	{
		point new_head = m_body.front();
	
		switch (m_direction)
		{
		case app::direction::UP:
			new_head.y -= UNIT_SIZE;
			break;

		case app::direction::DOWN:
			new_head.y += UNIT_SIZE;
			break;

		case app::direction::RIGHT:
			new_head.x += UNIT_SIZE;
			break;

		case app::direction::LEFT:
			new_head.x -= UNIT_SIZE;
			break;
		}

		m_body.push_front(new_head);
	}
	bool snake::check_if_snake_eat_himself() const
	{

		point head_location = m_body.front();
		auto iterator = m_body.begin();
		
		for (iterator++; iterator != m_body.end(); iterator++)
		{
			if (*iterator == head_location) return true;
		}

		return false;
	}
}