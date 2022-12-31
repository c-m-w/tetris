/// window.hpp

#pragma once

using fn_key_callback = std::function<void(void)>;
using fn_mouse_callback = std::function<void(unsigned const, unsigned const)>;

class window : public i_base<window>
{
private:

	struct key_callback_t
	{
		fn_key_callback callback;
		unsigned key;
		unsigned id;

		key_callback_t(fn_key_callback const callback,
					   unsigned const key,
					   unsigned const id) :
			callback(callback), key(key), id(id)
		{ }
	};

	struct mouse_callback_t
	{
		fn_mouse_callback callback;
		unsigned id;

		mouse_callback_t(fn_mouse_callback const callback,
						 unsigned const id) :
			callback(callback), id(id)
		{ }
	};

	constexpr static auto WINDOW_NAME = "test";
	GLFWwindow* wnd;
	std::vector<key_callback_t> key_callbacks {};
	std::vector<mouse_callback_t> mouse_callbacks {};
	unsigned callback_counter = 0u;

	static void key_press(GLFWwindow* wnd, int key, int scancode, int action, int mods);
	static void mouse_button_press(GLFWwindow* wnd, int key, int action, int mods);
	static void mouse_move(GLFWwindow* wnd, double x, double y);

public:

	bool init() override;
	bool shutdown() override;

	unsigned add_key_callback(fn_key_callback const callback, unsigned key);
	void remove_key_callback(unsigned id);
	unsigned add_mouse_callback(fn_mouse_callback const callback);
	void remove_mouse_callback(unsigned id);

	void update();

	friend class render_engine;
};
