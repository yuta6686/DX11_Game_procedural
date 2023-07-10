#include "stdafx.h"
#include "Tesselation.h"

void Tesselation::InitInside()
{
	m_Shader = new CShader();
	m_Shader->Init("shaderWaterVS.cso", "shaderWaterPS.cso");
	m_Shader->InitHallShader("testHS.cso");
	m_Shader->InitDomainShader("testDS.cso");

	m_Texture = new CTexture();
	m_Texture->Load("data/TEXTURE/field.tga");

	
	_useTesselation = false;

	m_Name = "Tesselation";
	MyImgui::flags[m_Name] = true;
}

void Tesselation::UninitInside()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_Texture->Unload();
	delete m_Texture;
}

void Tesselation::Update()
{
}

void Tesselation::DrawShadow()
{
}

void Tesselation::DrawImgui()
{
	if (!MyImgui::flags[m_Name])return;

	if (ImGui::TreeNode(m_Name.c_str()))
	{
		ImGui::Checkbox("Use Tesselation", &_useTesselation);

		ImGui::TreePop();		
	}
}
