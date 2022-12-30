/// render_engine.hpp

#pragma once

class render_engine : public i_base<render_engine>
{
private:

	constexpr static auto WINDOW_NAME = "test";

	GLFWwindow* window;
	unsigned default_program = 0u;
	unsigned texture_program = 0u;

	bool make_window();
	bool make_shader(unsigned& program, char const* const vs, char const* const fs);
	bool make_shaders();
	template<typename T, unsigned N>
	unsigned make_array_buffer(raw_vector<T, N> const & data, unsigned shader_index, unsigned vector_size);

public:

	bool init() override;
	bool shutdown() override;

	void begin_scene();
	void end_scene();

	void draw_primitive(primitive p, primitive_color c, bool const outline = false);
	void draw_textured_primitive(primitive p, uv u, unsigned texture_id);

	void draw_rect(location const & position,
				   dimension const & size,
				   color_t const& top_left,
				   color_t const& top_right,
				   color_t const& bottom_left,
				   color_t const& bottom_right,
				   bool const outlined = false);
	void draw_rect(location const& position,
				   dimension const& size,
				   color_t const& c,
				   bool const outlined = false);
	void draw_text(std::string const& text, unsigned size, color_t const& color, location top_left);
};
