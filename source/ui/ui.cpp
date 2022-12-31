/// ui.cpp

#include "../tetris.hpp"

using namespace ui_types;

void ui::mouse_click()
{
	if (auto& hovered_element = ui::get()->hovered_element)
		hovered_element->on_click();
}

void ui::mouse_move(unsigned const x, unsigned const y)
{
	auto& hovered_element = *&ui::get()->hovered_element;

	hovered_element && (hovered_element->hovered = false);

	hovered_element = find_hovered_children(x, y, &ui::get()->body);

	hovered_element && (hovered_element->hovered = true);
}

i_drawable * ui::find_hovered_children(unsigned const x, unsigned const y, container* const parent)
{
	i_drawable * hovered_element = parent;

	for (auto* const child : parent->children)
		if (child->contains_point(x, y))
		{
			hovered_element = child;
			break;
		}

	if (parent != hovered_element
		&& hovered_element->is_type(i_drawable::DRAWABLE_CONTAINER))
		return find_hovered_children(x, y, static_cast<container*>(hovered_element));

	return hovered_element;
}

ui::ui() :
	body({ 0, 0 }, { WINDOW_WIDTH, WINDOW_HEIGHT }, container::DRAW_NONE)
{ }

bool ui::init()
{
	window::get()->add_key_callback(mouse_click, GLFW_MOUSE_BUTTON_LEFT);
	window::get()->add_mouse_callback(mouse_move);

	return true;
}

bool ui::shutdown()
{
	return true;
}

container* const ui::get_body()
{
	return &body;
}

bool ui::is_element_hovered(ui_types::i_drawable* const element)
{
	return element == hovered_element;
}
