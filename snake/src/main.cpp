
#include <iostream>
#include <thread>
#include <time.h>

#include "snake.h"
#include "apple.h"
#include "renderer.h"


static app::snake snake(5);
static app::apple apple;
static bool lock_input = false;
static bool running = true;
static GLFWwindow* window = nullptr;

void check_collisions()
{
	const point& head = snake.get_head();

	if (snake.check_if_snake_eat_himself() or
		head.x < 0 or head.x > WIDTH - UNIT_SIZE or 
		head.y < 0 or head.y > HEIGHT - UNIT_SIZE)
	{
		running = false;
	}

	if (snake.get_head() == apple.get_location())
	{
		snake.inc_size_by_one();
		apple.respawn();
	}
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (lock_input) return;

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		if (snake.get_direction() != app::direction::DOWN)
			snake.set_direction(app::direction::UP);
	}
	else if (glfwGetKey(window, GLFW_KEY_D))
	{
		if (snake.get_direction() != app::direction::LEFT)
			snake.set_direction(app::direction::RIGHT);
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{
		if (snake.get_direction() != app::direction::UP)
			snake.set_direction(app::direction::DOWN);
	}
	else if (glfwGetKey(window, GLFW_KEY_A))
	{
		if (snake.get_direction() != app::direction::RIGHT)
			snake.set_direction(app::direction::LEFT);
	}

	lock_input = true;
}


int main()
{
	srand(time(0));

	if (!glfwInit())
	{
		std::cerr << "error at init glfwInit\n";
		system("pause");
		return -1;
	}
	window = glfwCreateWindow(WIDTH, HEIGHT, "snake game", nullptr, nullptr);

	if (!window)
	{
		std::cerr << "error at init glfwWindow\n";
		system("pause");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard_callback);
	
	GLenum error = glewInit();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "error at glewInit\n";
		system("pause");
		return -1;
	}

	renderer::init();

	while (running = running and !glfwWindowShouldClose(window))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		snake.update();
		check_collisions();
		lock_input = false;
		renderer::clear();

		snake.render();
		apple.render();
		renderer::render();
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	renderer::terminate();

	glfwTerminate();
}