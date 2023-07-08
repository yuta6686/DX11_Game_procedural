#include "stdafx.h"
#include "OperationExplanation.h"

void operation_explanation::Init()
{
	_nodeText = "OperationExplanation";
	_explanationText = "[WASD]:Camera Move\n[IJKL]:Target Move";	

	MyImgui::flags[_nodeText] = true;
}

void operation_explanation::Uninit()
{
}

void operation_explanation::Update()
{
}

void operation_explanation::Draw()
{
}

void operation_explanation::DrawImgui()
{
	if (!MyImgui::flags[_nodeText])return;

	ImGui::Begin(_nodeText.c_str());

		
	ImGui::Text(_explanationText.c_str());


	ImGui::End();
}
