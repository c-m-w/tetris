/// render_engine.cpp

#include "../tetris.hpp"

bool render_engine::make_window()
{
	glewExperimental = true;

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);

	if (nullptr == window)
		return false;

	glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit())
		return false;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

bool render_engine::make_shaders()
{
	auto const check_error = [](auto check_fn, auto id, auto status_to_check, auto get_log_fn) -> auto
	{
		auto result = GL_FALSE;
		auto log_length = 0;

		check_fn(id, status_to_check, &result);
		check_fn(id, GL_INFO_LOG_LENGTH, &log_length);

		if (0 != log_length)
		{
			std::string error;

			error.resize(log_length + 1);

			get_log_fn(id, log_length, nullptr, &error[0]);

			return false;
		}

		return true;
	};

	auto const make_shader = [check_error](auto type, auto const * const * src) -> auto
	{
		auto id = glCreateShader(type);
		auto result = GL_FALSE;
		auto log_length = 0;

		glShaderSource(id, 1, src, nullptr);
		glCompileShader(id);

		return check_error(glGetShaderiv, id, GL_COMPILE_STATUS, glGetShaderInfoLog)
			? id
			: 0u;
	};

	auto const vs_id = make_shader(GL_VERTEX_SHADER, &shaders::VS);
	auto const fs_id = make_shader(GL_FRAGMENT_SHADER, &shaders::FS);
	auto success = false;

	if (0 == vs_id
		|| 0 == fs_id)
		return false;

	program_id = glCreateProgram();

	glAttachShader(program_id, vs_id);
	glAttachShader(program_id, fs_id);

	glLinkProgram(program_id);

	if ((success = check_error(glGetProgramiv, program_id, GL_LINK_STATUS, glGetProgramInfoLog)))
		glUseProgram(program_id);

	glDetachShader(program_id, vs_id);
	glDetachShader(program_id, fs_id);

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);

	return success;
}

bool render_engine::init()
{
	return make_window()
			&& make_shaders();
}

bool render_engine::shutdown()
{
	return true;
}

void render_engine::begin_scene()
{
	glClearColor(0.f, 0.f, 0.4f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render_engine::end_scene()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void render_engine::draw_primitive(primitive p, primitive_color c)
{
	auto const make_array_buffer = [](auto data, auto shader_index) -> auto
	{
		auto id = 0u;

		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, data.size(), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(shader_index);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glVertexAttribPointer(shader_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		return id;
	};

	auto array_id = 0u;

	glGenVertexArrays(1, &array_id);
	glBindVertexArray(array_id);

	auto const vertex_id = make_array_buffer(p, 0);
	auto const color_id = make_array_buffer(c, 1);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glDeleteBuffers(1, &vertex_id);
	glDeleteBuffers(1, &color_id);
}
