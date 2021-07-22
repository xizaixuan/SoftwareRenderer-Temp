#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <cstdlib>

struct Material
{
	int baseColorTexture;

	Material()
	{
		baseColorTexture = -1;
	}
};

#endif
