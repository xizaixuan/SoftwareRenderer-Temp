#ifndef _Pipeline_H_
#define _Pipeline_H_

#include <vector>
#include "Mathematics/Float3.h"
#include "Mathematics/Float4.h"
#include "Mathematics/Float2.h"

using namespace std;

class Camera;
class Mesh;

namespace Pipeline
{
	void Execute(Camera* camera, const Mesh& mesh);

	void Rasterize(float4 v0, float4 v1, float4 v2, float3 color0, float3 color1, float3 color2);
};

#endif