#include "Pipeline.h"
#include "Camera.h"
#include "Mathematics\MathUtil.h"
#include "Framework\RenderContext.h"
#include <cmath>
#include "Framework\RenderDevice.h"

using namespace std;

void Pipeline::Execute(Camera* camera, vector<float3> vertices, vector<int> indices, vector<float3> colors)
{
	camera->BuildViewMatrix();
	camera->BuildPerspectiveMatrix();
	camera->BuildViewPortMatrix();

	auto viewMat = camera->GetViewMatrix();
	auto projMat = camera->GetPerspectiveMatrix();
	auto viewPortMat = camera->GetViewPortMatrix();
	auto vp = viewMat * projMat;

	vector<float4> vertexArray;
	for (auto vertex : vertices)
	{
		auto point = float4(vertex, 1.0);
		point = point * vp;

		point = MathUtil::Homogenous(point);

		point = point * viewPortMat;

		vertexArray.push_back(point);
	}

	int indexLength = indices.size();
	for (int index = 0; index < indexLength; index += 3)
	{
		auto v0 = vertexArray[indices[index + 0]];
		auto v1 = vertexArray[indices[index + 1]];
		auto v2 = vertexArray[indices[index + 2]];

		auto color0 = colors[indices[index + 0]];
		auto color1 = colors[indices[index + 1]];
		auto color2 = colors[indices[index + 2]];

		Rasterize(v0, v1, v2, color0, color1, color2);
	}
}

void Pipeline::Rasterize(float4 v0, float4 v1, float4 v2, float3 color0, float3 color1, float3 color2)
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

	int area = edgeFunction(v0, v1, v2);

	auto minX = std::lround(boundMin(v0.x, v1.x, v2.x));
	auto maxX = std::lround(boundMax(v0.x, v1.x, v2.x));
	auto minY = std::lround(boundMin(v0.y, v1.y, v2.y));
	auto maxY = std::lround(boundMax(v0.y, v1.y, v2.y));

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			auto point = float4(x + 0.5f, y + 0.5f, 0.0, 1.0);
			float w0 = edgeFunction(v1, v2, point);
			float w1 = edgeFunction(v2, v0, point);
			float w2 = edgeFunction(v0, v1, point);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area;
				w1 /= area;
				w2 /= area;

				//////////////////////////////////////////////////////////////////////////
				// color
				float3 newColor = color0 * w0 + color1 * w1 + color2 * w2;

				DWORD color = (255 << 24) + ((int)(newColor.x * 255) << 16) + ((int)(newColor.y * 255) << 8) + (int)(newColor.z * 255);

				RenderDevice::GetSingletonPtr()->DrawPixel(x, y, color);
			}
		}
	}
}