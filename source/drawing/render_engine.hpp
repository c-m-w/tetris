/// render_engine.hpp

#pragma once

using color_t = vector<float, 3>;
using primitive = raw_vector<coordinate<relative_t>, 3>;
using primitive_color = raw_vector<color_t, 3>;

class render_engine : public i_base<render_engine>
{
private:

	constexpr static auto WINDOW_NAME = "test";

	GLFWwindow* window;
	unsigned program_id = 0u;

	bool make_window();
	bool make_shaders();

public:

	bool init() override;
	bool shutdown() override;

	void begin_scene();
	void end_scene();

	void draw_primitive(primitive p, primitive_color c);
	void draw_triangle(primitive p, primitive_color c);
};
