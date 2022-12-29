/// shaders.hpp

#pragma once

namespace shaders
{
	const char* const VS = R"(
		#version 330 core

		layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;

		out vec3 fragment_color;

		void main( )
		{
			gl_Position.xyz = position;
			gl_Position.w = 1.0;

			fragment_color = color;
		}
	)";

	const char* const FS = R"(
		#version 330 core

		in vec3 fragment_color;
		out vec3 color;
	
		void main( )
		{
			color = fragment_color;
		}
	)";
}
