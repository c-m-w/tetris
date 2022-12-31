/// render_engine.cpp

#include "../tetris.hpp"

bool render_engine::make_window()
{
	if (GLEW_OK != glewInit())
		return false;

	glfwSetInputMode(window::get()->wnd, GLFW_STICKY_KEYS, GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool render_engine::make_shader(unsigned& program, char const* const vs, char const* const fs)
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

	auto const vs_id = make_shader(GL_VERTEX_SHADER, &vs);
	auto const fs_id = make_shader(GL_FRAGMENT_SHADER, &fs);
	auto success = false;

	if (0 == vs_id
		|| 0 == fs_id)
		return false;

	program = glCreateProgram();

	glAttachShader(program, vs_id);
	glAttachShader(program, fs_id);

	glLinkProgram(program);

	if (!(success = check_error(glGetProgramiv, program, GL_LINK_STATUS, glGetProgramInfoLog)))
	{
		// todo handle error
	}

	glDetachShader(program, vs_id);
	glDetachShader(program, fs_id);

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);

	return success;
}

bool render_engine::make_shaders()
{
	return make_shader(default_program, shaders::VS_DEFAULT, shaders::FS_DEFAULT)
		&& make_shader(texture_program, shaders::VS_TEXTURE, shaders::FS_TEXTURE);
}

template<typename T, unsigned N>
unsigned render_engine::make_array_buffer(raw_vector<T, N> const & data, unsigned shader_index, unsigned vector_size)
{
	auto id = 0u;

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size(), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader_index);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glVertexAttribPointer(shader_index, vector_size, GL_FLOAT, GL_FALSE, 0, nullptr);

	return id;
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
	glClearColor(0.f, 0.f, 0.0f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render_engine::end_scene()
{
	glfwSwapBuffers(window::get()->wnd);
	window::get()->update();
}

void render_engine::draw_primitive(primitive p, primitive_color c, bool const outline)
{
	auto array_id = 0u;

	glGenVertexArrays(1, &array_id);
	glBindVertexArray(array_id);

	auto const vertex_id = make_array_buffer(p, 0, 3);
	auto const color_id = make_array_buffer(c, 1, 4);

	glUseProgram(default_program);
	glDrawArrays(outline ? GL_LINE_STRIP : GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glDeleteBuffers(1, &vertex_id);
	glDeleteBuffers(1, &color_id);
	glDeleteVertexArrays(1, &array_id);
}

void render_engine::draw_textured_primitive(primitive p, uv u, unsigned texture_id)
{
	auto array_id = 0u;

	glGenVertexArrays(1, &array_id);
	glBindVertexArray(array_id);

	auto const vertex_id = make_array_buffer(p, 0, 3);
	auto const uv_id = make_array_buffer(u, 1, 3);

	glUseProgram(texture_program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glDeleteBuffers(1, &vertex_id);
	glDeleteBuffers(1, &uv_id);
	glDeleteVertexArrays(1, &array_id);
}

void render_engine::draw_rect(location const& position,
							  dimension const& size,
							  color_t const& top_left,
							  color_t const& top_right,
							  color_t const& bottom_left,
							  color_t const& bottom_right,
							  bool const outlined)
{
	auto const p1 = primitive(coordinate<pixel_t>(position[0] + size[0], position[1]).to_relative(),
		coordinate<pixel_t>(position[0], position[1]).to_relative(),
		coordinate<pixel_t>(position[0], position[1] + size[1]).to_relative());
	auto const p2 = primitive(coordinate<pixel_t>(position[0], position[1] + size[1]).to_relative(),
		coordinate<pixel_t>(position[0] + size[0], position[1] + size[1]).to_relative(),
		coordinate<pixel_t>(position[0] + size[0], position[1]).to_relative());
	auto const c1 = primitive_color(top_right,
		top_left,
		bottom_left);
	auto const c2 = primitive_color(bottom_left, 
		bottom_right, 
		top_right);

	draw_primitive(p1, c1, outlined);
	draw_primitive(p2, c2, outlined);
}

void render_engine::draw_rect(location const& position,
							  dimension const& size,
							  color_t const& c,
							  bool const outlined)
{
	draw_rect(position, size, c, c, c, c, outlined);
}

void render_engine::draw_text(std::string const& text, unsigned size, color_t const& color, location top_left)
{
	auto const bmp = font_engine::get()->make_bitmap(text, size, color).format();

	auto const p1 = primitive(coordinate<pixel_t>(top_left[0] + bmp.width(), top_left[1]).to_relative(),
		coordinate<pixel_t>(top_left[0], top_left[1]).to_relative(),
		coordinate<pixel_t>(top_left[0], top_left[1] + bmp.height()).to_relative());

	auto const p2 = primitive(coordinate<pixel_t>(top_left[0], top_left[1] + bmp.height()).to_relative(),
		coordinate<pixel_t>(top_left[0] + bmp.width(), top_left[1] + bmp.height()).to_relative(),
		coordinate<pixel_t>(top_left[0] + bmp.width(), top_left[1]).to_relative());

	auto texture_id = 0u;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.width(), bmp.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.pixels());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	auto const u1 = uv(coordinate<relative_t>(1.f, 0.f),
					   coordinate<relative_t>(0.f, 0.f),
					   coordinate<relative_t>(0.f, 1.f));

	auto const u2 = uv(coordinate<relative_t>(0.f, 1.f),
					   coordinate<relative_t>(1.f, 1.f),
					   coordinate<relative_t>(1.f, 0.f));

	draw_textured_primitive(p1, u1, texture_id);
	draw_textured_primitive(p2, u2, texture_id);

	glDeleteTextures(1, &texture_id);
}
