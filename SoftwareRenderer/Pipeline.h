#ifndef _Pipeline_H_
#define _Pipeline_H_

#include <vector>
#include <tuple>
#include "Mathematics/Float3.h"
#include "Mathematics/Float4.h"
#include "Mathematics/Float2.h"
#include "Framework/Material.h"
#include "Framework/Texture.h"

using namespace std;

class Camera;
class Mesh;

namespace Pipeline
{
	void Execute(Camera* camera, const Mesh& mesh, const vector<Texture>& textures, const vector<Material>& materials);

	void Rasterize(tuple<float4, float2> v0, tuple<float4, float2> v1, tuple<float4, float2> v2, const Texture& texture);
};

#endif