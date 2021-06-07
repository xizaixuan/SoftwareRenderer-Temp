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

	int indexLength = indices.size();
	for (int index = 0; index < indexLength; index += 3)
	{
		auto v0 = float4(vertices[indices[index + 0]], 1.0);
		auto v1 = float4(vertices[indices[index + 1]], 1.0);
		auto v2 = float4(vertices[indices[index + 2]], 1.0);

		v0 = v0 * vp;
		v1 = v1 * vp;
		v2 = v2 * vp;

		v0 = MathUtil::Homogenous(v0);
		v1 = MathUtil::Homogenous(v1);
		v2 = MathUtil::Homogenous(v2);

		v0 = v0 * viewPortMat;
		v1 = v1 * viewPortMat;
		v2 = v2 * viewPortMat;

// 		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
// 		RenderContext::DrawLine(v0.x, v0.y, v1.x, v1.y, color);
// 		RenderContext::DrawLine(v0.x, v0.y, v2.x, v2.y, color);
// 		RenderContext::DrawLine(v1.x, v1.y, v2.x, v2.y, color);
		Rasterize(v0, v1, v2);
	}
}

void Pipeline::Rasterize(float4 v0, float4 v1, float4 v2)
{
	float minX = MathUtil::maxValue;
	float maxX = MathUtil::minValue;
	float minY = MathUtil::maxValue;
	float maxY = MathUtil::minValue;

	if (v0.x < minX) minX = v0.x;

	if (v1.x < minX) minX = v1.x;

	if (v2.x < minX) minX = v2.x;

	if (v0.y < minY) minY = v0.y;

	if (v1.y < minY) minY = v1.y;

	if (v2.y < minY) minY = v2.y;

	if (v0.x > maxX) maxX = v0.x;

	if (v1.x > maxX) maxX = v1.x;

	if (v2.x > maxX) maxX = v2.x;

	if (v0.y > maxY) maxY = v0.y;

	if (v1.y > maxY) maxY = v1.y;

	if (v2.y > maxY) maxY = v2.y;

	for (int x = std::floor(minX); x <= std::ceil(maxX); x++)
	{
		for (int y = std::floor(minY); y <= std::ceil(maxY); y++)
		{
			if (IsInTriangle(float2(v0.x, v0.y), float2(v1.x, v1.y), float2(v2.x, v2.y), float2(x, y)))
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
