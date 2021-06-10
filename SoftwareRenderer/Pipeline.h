#ifndef _Pipeline_H_
#define _Pipeline_H_

#include <vector>
#include "Mathematics/Float3.h"
#include "Mathematics/Float4.h"
#include "Mathematics/Float2.h"

using namespace std;

class Camera;

namespace Pipeline
{
	void Execute(Camera* camera, vector<float3> vertices, vector<int> indices);

	void Rasterize(float4 v0, float4 v1, float4 v2);
};

#endif