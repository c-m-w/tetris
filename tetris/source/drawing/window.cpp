/// window.cpp

#include "../tetris.hpp"

void window::key_press(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
	if (GLFW_PRESS != action)
		return;

	for (auto & callback : window::get()->key_callbacks)
		if (key == callback.key)
			callback.callback();
}

void window::mouse_button_press(GLFWwindow* wnd, int key, int action, int mods)
{
	key_press(wnd, key, 0, action, mods);
}

void window::mouse_move(GLFWwindow* wnd, double x, double y)
{
	for (auto& callback : window::get()->mouse_callbacks)
		callback.callback(unsigned(x), unsigned(y));
}

bool window::init()
{
	glewExperimental = true;

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	wnd = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);

	if (nullptr == wnd)
		return false;

	glfwMakeContextCurrent(wnd);
	glfwSetKeyCallback(wnd, key_press);
	glfwSetMouseButtonCallback(wnd, mouse_button_press);
	glfwSetCursorPosCallback(wnd, mouse_move);

	return true;
}

bool window::shutdown()
{
	return false;
}

unsigned window::add_key_callback(fn_key_callback const callback, unsigned key)
{
	key_callbacks.emplace_back(callback, key, callback_counter);

	return callback_counter++;
}

void window::remove_key_callback(unsigned id)
{
	auto const it = std::find_if(key_callbacks.begin(),
								 key_callbacks.end(),
								 [id](auto i) { return i.id == id; });

	if (key_callbacks.end() == it)
		return;

	key_callbacks.erase(it);
}

unsigned window::add_mouse_callback(fn_mouse_callback const callback)
{
	mouse_callbacks.emplace_back(callback, callback_counter);

	return callback_counter++;
}

void window::remove_mouse_callback(unsigned id)
{
	auto const it = std::find_if(mouse_callbacks.begin(),
								 mouse_callbacks.end(),
								 [id](auto i) { return i.id == id; });

	if (mouse_callbacks.end() == it)
		return;

	mouse_callbacks.erase(it);
}

void window::update()
{
	glfwPollEvents();
	should_exit = 0 != glfwWindowShouldClose(wnd);
}
