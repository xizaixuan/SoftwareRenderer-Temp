#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <cstdlib>

class Material
{
public:
	int baseColorTexture;

	Material()
	{
		baseColorTexture = -1;
	}
};

#endif
