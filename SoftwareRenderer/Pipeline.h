#ifndef _Pipeline_H_
#define _Pipeline_H_

#include <vector>
#include "Mathematics/Float3.h"

using namespace std;

class Camera;

class Pipeline
{
	void Execute(Camera* camera, vector<float3> vertices, vector<int> indices);
};

#endif