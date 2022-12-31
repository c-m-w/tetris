/// types.hpp

#pragma once

class color_t : public vector<float, 4>
{
public:

	color_t() :
		vector()
	{}

	color_t(float const r, float const g, float const b, float const a):
		vector{ r, g, b, a }
	{ }

	color_t(unsigned const rgba):
		vector{float((rgba & 0xFF000000) >> 24) / float(0xFF),
			   float((rgba & 0x00FF0000) >> 16) / float(0xFF),
			   float((rgba & 0x0000FF00) >> 8) / float(0xFF),
			   float((rgba & 0x000000FF) >> 0) / float(0xFF)}
	{ }

	color_t& operator=(unsigned const rgba)
	{
		*this = color_t(rgba);

		return *this;
	}

	unsigned hex() const
	{
		// NOTE: actually needs to be stored as abgr for rgba
		return unsigned((*this)[3] * 0xFF) << 24
				| unsigned((*this)[2] * 0xFF) << 16
				| unsigned((*this)[1] * 0xFF) << 8
				| unsigned((*this)[0] * 0xFF) << 0;
	}
};

using primitive = raw_vector<coordinate<relative_t>, 3>;
using primitive_color = raw_vector<color_t, 3>;
using uv = raw_vector<coordinate<relative_t>, 3>;
using location = coordinate<pixel_t>;
using dimension = coordinate<pixel_t>;
