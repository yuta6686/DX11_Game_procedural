#include "stdafx.h"
#include "spheres.h"

void Spheres::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	const float scale = 0.1;
	m_Scale = XMFLOAT3(scale, scale, scale);

	Load("data/MODEL/sphere.obj");

	m_Shader = new CShader();
	m_Shader->Init("InstancingVS.cso", "InstancingPS.cso");

	m_Name = "Sphere";
	_mydata._parameter2.x = 500;
	_mydata._parameter2.y = 4.3;

	_count = 500;
}
