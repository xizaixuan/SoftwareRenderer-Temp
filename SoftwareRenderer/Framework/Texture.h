#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <cstdlib>

class Texture
{
public:
    int width;
    int height;
	int components;
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
