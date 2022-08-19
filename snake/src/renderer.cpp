#include "renderer.h"

#include <memory>
#include "shader.h"
#include <vendor/glm/ext/matrix_clip_space.hpp>

namespace renderer
{
	struct vertex
	{
		float position[2];
		float color[3];
	};

	namespace
	{
		const size_t max_quads = 100;
		const size_t max_vertices = max_quads * 4;
		const size_t max_indices = max_quads * 6;
		size_t quads_count = 0;

		glm::vec3 color = glm::vec3(1, 1, 1);
		
		std::unique_ptr<opengl::shader> shader;
		uint32_t vbo;
		uint32_t ibo;

	}

	void init()
	{
		shader = std::make_unique<opengl::shader>("res/vert.shader", "res/frag.shader");
		
		shader->bind();
		shader->set_uniform_mat4f("u_mvp", glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f));
		
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, max_vertices * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)offsetof(vertex, color));


		uint32_t indices[max_indices];
		uint32_t offset = 0;

		for (size_t i = 0; i < max_indices; i += 6)
		{
			indices[i    ] = 0 + offset;  
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		glCreateBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void terminate()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

	void set_color(float r, float g, float b)
	{
		color.r = r;
		color.g = g;
		color.b = b;
	}


	void quad(float x, float y, float w, float h)
	{
		if (quads_count == max_quads)
		{
			render();
		}

		vertex positions[] = {
			{x + w, y	 , color.r, color.g, color.b}, 
			{x	  , y	 , color.r, color.g, color.b},
			{x	  , y + h, color.r, color.g, color.b},
			{x + w, y + h, color.r, color.g, color.b}
		};
	
		glBufferSubData(GL_ARRAY_BUFFER, quads_count * 4 * sizeof(vertex), sizeof(positions), positions);
		quads_count++;	
	}

	void render()
	{
		glDrawElements(GL_TRIANGLES, quads_count * 6, GL_UNSIGNED_INT, nullptr);
		quads_count = 0;
	}

	void clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}



