#ifndef SAMPLER2D_H_
#define SAMPLER2D_H_

#include <cstdlib>
#include <windows.h>

class Texture;

struct Sampler2D
{
public:
	DWORD Sample(const Texture& texture, float u, float v);

public:
	int minFilter;
	int magFilter;
	int wrapS;
	int wrapT;
};

#endif