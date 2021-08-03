#include "Pipeline.h"
#include "Camera.h"
#include "Mathematics\MathUtil.h"
#include "Framework\RenderContext.h"
#include <cmath>
#include "Framework\RenderDevice.h"
#include "Framework\Mesh.h"
#include "Framework\Sampler2D.h"

using namespace std;

void Pipeline::Execute(Camera* camera, const Mesh& mesh, const vector<Texture>& textures, const vector<Material>& materials)
{
	camera->BuildViewMatrix();
	camera->BuildPerspectiveMatrix();
	camera->BuildViewPortMatrix();

	auto viewMat = camera->GetViewMatrix();
	auto projMat = camera->GetPerspectiveMatrix();
	auto viewPortMat = camera->GetViewPortMatrix();
	auto vp = viewMat * projMat;

	auto material = materials[mesh.material_ids[0]];
	auto texture = textures[material.baseColorTexture];

	vector<float4> vertexArray;
	for (auto vertex : mesh.vertices)
	{
		auto point = float4(vertex, 1.0) * mesh.pivotXform;
		point = point * vp;

		point = MathUtil::Homogenous(point);

		point = point * viewPortMat;

		vertexArray.push_back(point);
	}

	int indexLength = mesh.indices.size();
	for (int index = 0; index < indexLength; index += 3)
	{
		auto v0 = vertexArray[mesh.indices[index + 0]];
		auto v1 = vertexArray[mesh.indices[index + 1]];
		auto v2 = vertexArray[mesh.indices[index + 2]];

		auto uv0 = mesh.uvs[index + 0];
		auto uv1 = mesh.uvs[index + 1];
		auto uv2 = mesh.uvs[index + 2];

		//auto color0 = colors[indices[index + 0]];
		//auto color1 = colors[indices[index + 1]];
		//auto color2 = colors[indices[index + 2]];

		Rasterize(
			tuple<float4, float2>(v0, uv0),
			tuple<float4, float2>(v1, uv1),
			tuple<float4, float2>(v2, uv2), texture);
		//DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
		//RenderContext::DrawLine(v0.x, v0.y, v1.x, v1.y, color);
		//RenderContext::DrawLine(v0.x, v0.y, v2.x, v2.y, color);
		//RenderContext::DrawLine(v2.x, v2.y, v1.x, v1.y, color);
	}
}

void Pipeline::Rasterize(tuple<float4, float2> v0, tuple<float4, float2> v1, tuple<float4, float2> v2, const Texture& texture)
{
	auto edgeFunction = [](const float4& a, const float4& b, const float4& c)
	{
		return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	};

	auto boundMin = [](const float& a, const float& b, const float& c)
	{
		return min(min(a, b), min(a, c));
	};

	auto boundMax = [](const float& a, const float& b, const float& c)
	{
		return max(max(a, b), max(a, c));
	};

	Sampler2D sampler;

	auto position0 = get<0>(v0);
	auto position1 = get<0>(v1);
	auto position2 = get<0>(v2);

	auto uv0 = get<1>(v0);
	auto uv1 = get<1>(v1);
	auto uv2 = get<1>(v2);

	int area = edgeFunction(position0, position1, position2);

	auto minX = std::lround(boundMin(position0.x, position1.x, position2.x));
	auto maxX = std::lround(boundMax(position0.x, position1.x, position2.x));
	auto minY = std::lround(boundMin(position0.y, position1.y, position2.y));
	auto maxY = std::lround(boundMax(position0.y, position1.y, position2.y));

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			auto point = float4(x + 0.5f, y + 0.5f, 0.0, 1.0);
			float w0 = edgeFunction(position1, position2, point);
			float w1 = edgeFunction(position2, position0, point);
			float w2 = edgeFunction(position0, position1, point);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area;
				w1 /= area;
				w2 = 1 - w0 - w1;

				//////////////////////////////////////////////////////////////////////////
				// color
// 				float3 newColor = color0 * w0 + color1 * w1 + color2 * w2;
// 
// 				DWORD color = (255 << 24) + ((int)(newColor.x * 255) << 16) + ((int)(newColor.y * 255) << 8) + (int)(newColor.z * 255);

				
				//////////////////////////////////////////////////////////////////////////
				// UV
				float2 uv = uv0 * w0 + uv1 * w1 + uv2 * w2;

				while (uv.x < 0)
				{
					uv.x += 1;
				}

				while (uv.x > 1)
				{
					uv.x -= 1;
				}

				while (uv.y < 0)
				{
					uv.y += 1;
				}

				while (uv.y > 1)
				{
					uv.y -= 1;
				}

				auto color = sampler.Sample(texture, uv.x, uv.y);
				RenderDevice::GetSingletonPtr()->DrawPixel(x, y, color);
			}
		}
	}
}