#include "Sampler2D.h"
#include "Texture.h"

int Sampler2D::Sample(const Texture& texture, float u, float v)
{
	int w = texture.width - 1;
	int h = texture.height - 1;

	int offset = (texture.width * h * v + u * w) * texture.components;

	int r = texture.image[offset + 0];
	int g = texture.image[offset + 1];
	int b = texture.image[offset + 2];

	int color = (255 << 24) + ((r * 255) << 16) + ((b * 255) << 8) + (b * 255);

	return color;
}