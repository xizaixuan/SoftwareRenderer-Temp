#include "Pipeline.h"
#include "Camera.h"
#include "Mathematics\MathUtil.h"
#include "Framework\RenderContext.h"
#include <cmath>
#include "Framework\RenderDevice.h"

using namespace std;

void Pipeline::Execute(Camera* camera, vector<float3> vertices, vector<int> indices)
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

		Rasterize(v0, v1, v2);
	}
}

void Pipeline::Rasterize(float4 v0, float4 v1, float4 v2)
{
	auto boundMin = [](const float& a, const float& b, const float& c)
	{
		return min(min(a, b), min(a, c));
	};

	auto boundMax = [](const float& a, const float& b, const float& c)
	{
		return max(max(a, b), max(a, c));
	};

	auto minX = std::lround(boundMin(v0.x, v1.x, v2.x));
	auto maxX = std::lround(boundMax(v0.x, v1.x, v2.x));
	auto minY = std::lround(boundMin(v0.y, v1.y, v2.y));
	auto maxY = std::lround(boundMax(v0.y, v1.y, v2.y));

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			if (IsInTriangle(float2(v0.x, v0.y), float2(v1.x, v1.y), float2(v2.x, v2.y), float2(x + 0.5f, y + 0.5f)))
			{
				DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
				RenderDevice::GetSingletonPtr()->DrawPixel(x, y, color);
			}
		}
	}
}

bool Pipeline::IsInTriangle(float2 v0, float2 v1, float2 v2, float2 point)
{
	auto pv0 = point - v0;
	auto pv1 = point - v1;
	auto pv2 = point - v2;
	auto v01 = v0 - v1;
	auto v12 = v1 - v2;
	auto v20 = v2 - v0;

	auto value0 = pv0.x * v01.y - pv0.y * v01.x;
	auto value1 = pv1.x * v12.y - pv1.y * v12.x;
	auto value2 = pv2.x * v20.y - pv2.y * v20.x;

	return value0 >= 0 && value1 >= 0 && value2 >= 0;
}
