#include "stdafx.h"
#include "torii_hull.h"

void ToriiHull::Init()
{
	InitTransform();

	Load("data/MODEL/torii.obj");	

	InitShader("InstancingVS.cso", "InstancingPS.cso");

	InitName("ToriiHull");
}

void ToriiHull::Update()
{
}

void ToriiHull::DrawImgui()
{
}
