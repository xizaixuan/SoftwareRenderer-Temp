#ifndef SAMPLER2D_H_
#define SAMPLER2D_H_

#include <cstdlib>

class Texture;

struct Sampler2D
{
public:
	int Sample(const Texture& texture, float u, float v);

public:
	int minFilter;
	int magFilter;
	int wrapS;
	int wrapT;
};

#endif