#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#define WIDTH 750
#define HEIGHT 600
#define UNIT_SIZE 25

namespace renderer
{
	void init();
	void terminate();

	void set_color(float r, float g, float b);
	void quad(float x, float y, float w, float h);
	void render();
	void clear();
}