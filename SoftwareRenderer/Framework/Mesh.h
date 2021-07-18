#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include "../Mathematics/Float3.h"
#include "../Mathematics/Float2.h"
#include "../Mathematics/Float4.h"
#include "../Mathematics/Matrix.h"


using namespace std;

class Mesh
{
 public:
	Mesh(const size_t vertex_stride) :
		stride(vertex_stride)
	{
	}

	string name;
		
	vector<float3> vertices;
	vector<float2> uvs;
	vector<float3> normals;
	vector<float4> vertexColors;
	vector<unsigned int> indices;
	vector<unsigned int> material_ids;

	Matrix pivotXform;
	size_t stride;
};


#endif
