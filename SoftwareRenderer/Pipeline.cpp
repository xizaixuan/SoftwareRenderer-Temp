#include "Pipeline.h"
#include "Camera.h"
#include "Mathematics\MathUtil.h"
#include "Framework\RenderContext.h"

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

		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
		RenderContext::DrawLine(v0.x, v0.y, v1.x, v1.y, color);
		RenderContext::DrawLine(v0.x, v0.y, v2.x, v2.y, color);
		RenderContext::DrawLine(v1.x, v1.y, v2.x, v2.y, color);
	}
}