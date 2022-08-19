#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>


#include "renderer.h"

namespace opengl
{
	
	class shader
	{
	public:
		shader(const char* vert_filepath, const char* frag_filepath);
		~shader();
		void bind() const;
		void set_uniform_mat4f(const char* name, const glm::mat4& mat);
	private:
		uint32_t m_rendererID;
		std::unordered_map<const char*, int32_t> m_uniform_cache;

		static uint32_t compile_shader(int type, const char* src);
		static std::string load_shader(const char* filepath);
		
		int32_t get_uniform_location(const char* name);
	};
}