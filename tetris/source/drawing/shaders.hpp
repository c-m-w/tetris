/// shaders.hpp

#pragma once

namespace shaders
{
	const char* const VS_DEFAULT = R"(
		#version 330 core

		layout(location = 0) in vec3 position;
		layout(location = 1) in vec4 color;

		out vec4 fragment_color;

		void main( )
		{
			gl_Position.xyz = position;
			gl_Position.w = 1.0;

			fragment_color = color;
		}
	)";

	const char* const FS_DEFAULT = R"(
		#version 330 core

		in vec4 fragment_color;
		out vec4 color;
	
		void main( )
		{
			color = fragment_color;
		}
	)";

	const char* const VS_TEXTURE = R"(
		#version 330 core

		layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 uvw;

		out vec3 translated_uvw;

		void main( )
		{
			gl_Position.xyz = position;
			gl_Position.w = 1.0;

			translated_uvw = uvw;
		}
	)";

	const char* const FS_TEXTURE = R"(
		#version 330 core

		in vec3 translated_uvw;
		out vec4 color;

		uniform sampler2D sampler;
	
		void main( )
		{
			color = texture(sampler, vec2(translated_uvw.x, translated_uvw.y));
		}
	)";
}
