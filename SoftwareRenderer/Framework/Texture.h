#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <cstdlib>

struct Texture
{
    int width;
    int height;
	int components;
	int _pad_;
	unsigned char* image;

	Texture()
    {
		width = -1;
		height = -1;
		components = -1;
		image = NULL;
	}
};

#endif
