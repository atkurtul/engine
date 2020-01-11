#include "std/xf_str.h"
#include "buffer.h"
#include "font.h"

font::font(const char* path, float scale)
{
	xfstr data;
	std::ifstream s(path);
	data.getline(s);
	data.substr(data.find("size") - data.begin() + 5, 3) >> line;
	line *= scale;
	data.getline(s);
	data.getline(s);
	atlas = texture(data.exbtwn('"', '"'));
	data.getline(s);
	while (data.getline(s))
	{
		int id;
		Char c;
		float x, y, width, height, xoff, yoff;
		data.substr(data.find("id") - data.begin() + 3, 3) >> id;
		data.substr(data.find("x") - data.begin() + 2, 3) >> x;
		data.substr(data.find("y") - data.begin() + 2, 3) >> y;
		data.substr(data.find("width") - data.begin() + 6, 3) >> width;
		data.substr(data.find("height") - data.begin() + 7, 3) >> height;
		data.substr(data.find("xoffset") - data.begin() + 8, 3) >> xoff;
		data.substr(data.find("yoffset") - data.begin() + 8, 3) >> yoff;
		data.substr(data.find("xadvance") - data.begin() + 9, 3) >> c.advance;
		float x1 = (x + width) / atlas.size.x;
		float y1 = (y + height) / atlas.size.y;
		x /= atlas.size.x;
		y /= atlas.size.y;
		c.quad.gen();

		width *= scale;
		height *= scale;
		xoff *= scale;
		yoff *= scale;
		c.advance *= scale;
		float o = line - height - yoff;
		buffer(xfvec<float>{xoff, o, width + xoff, o, xoff, height + o, width + xoff, height + o });
		c.quad.attrib(0, 2, 0, 0);
		buffer(xfvec<float>{x, y1, x1, y1, x, y, x1, y});
		c.quad.attrib(1, 2, 0, 0);
		charmap[id] = c;
	}
}
