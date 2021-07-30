#include "Sampler2D.h"
#include "Texture.h"

DWORD Sampler2D::Sample(const Texture& texture, float u, float v)
{
	int tx = u * texture.width;
	int ty = v * texture.height;
	int idx_offset = (ty * texture.width + tx) * texture.components;
	int r = texture.image[idx_offset + 0];
	int g = texture.image[idx_offset + 1];
	int b = texture.image[idx_offset + 2];

	DWORD color = (b << 16) + (g << 8) + b;

	return color;
}