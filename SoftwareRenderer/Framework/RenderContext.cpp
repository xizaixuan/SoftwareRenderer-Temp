#include "RenderContext.h"
#include "Framework/RenderDevice.h"

void RenderContext::DrawLine(int x0, int y0, int x1, int y1, DWORD color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;

	while (x0 != x1 || y0 != y1)
	{
		RenderDevice::getSingletonPtr()->DrawPixel(x0, y0, color);

		int e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}
