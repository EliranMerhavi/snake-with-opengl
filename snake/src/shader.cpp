#include "shader.h"

namespace opengl
{
	shader::shader(const char* vert_filepath, const char* frag_filepath)
	{
		m_rendererID = glCreateProgram();

		std::string vert_src = load_shader(vert_filepath);
		std::string frag_src = load_shader(frag_filepath);

		uint32_t vs = compile_shader(GL_VERTEX_SHADER, vert_src.c_str());
		uint32_t fs = compile_shader(GL_FRAGMENT_SHADER, frag_src.c_str());

		glAttachShader(m_rendererID, vs);
		glAttachShader(m_rendererID, fs);

		glLinkProgram(m_rendererID);
		glValidateProgram(m_rendererID);

		glDeleteShader(vs);
		glDeleteShader(fs);

	}

	shader::~shader()
	{
		glDeleteProgram(m_rendererID);
	}

	void shader::bind() const
	{
		glUseProgram(m_rendererID);
	}

	void shader::set_uniform_mat4f(const char* name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &mat[0][0]);
	}

	uint32_t shader::compile_shader(int type, const char* src)
	{
		uint32_t id = glCreateShader(type);

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			std::cerr << "failed compiling shader\n";
			
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			
			char* msg = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, msg);

			std::cout << msg << '\n';
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	std::string shader::load_shader(const char* filepath)
	{
		std::ifstream ifs(filepath);

		if (ifs.fail())
		{
			std::cerr << "failed load shader\n";
			return "";
		}

		std::string content, line;

		while (std::getline(ifs, line))
		{
			content += line + '\n';
		}

		ifs.close();

		return content;
	}

	int32_t shader::get_uniform_location(const char* name)
	{
		if (m_uniform_cache.find(name) == m_uniform_cache.end())
		{
			m_uniform_cache[name] = glGetUniformLocation(m_rendererID, name);
		}

		return m_uniform_cache[name];
	}
}