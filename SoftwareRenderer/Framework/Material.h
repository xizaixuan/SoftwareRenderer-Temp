#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <cstdlib>

struct Material
{
	float diffuse[3];
	float specular[3];
	
	int id;
	int diffuse_texid;
	int specular_texid;

	Material()
	{
		diffuse[0] = 0.5;
		diffuse[1] = 0.5;
		diffuse[2] = 0.5;
		specular[0] = 0.5;
		specular[1] = 0.5;
		specular[2] = 0.5;

		id = -1;
		diffuse_texid = -1;
		specular_texid = -1;
	}
};

#endif
