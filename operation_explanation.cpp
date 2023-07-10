#include "stdafx.h"
#include "operation_explanation.h"

void OperationExplanation::Init()
{
	_nodeText = "OperationExplanation";
	_explanationText = 
		"[WASD]:Camera Move\n[E]Up[Q]Down\n[IJKL]:Target Move";		

	MyImgui::flags[_nodeText] = true;
}

void OperationExplanation::Uninit()
{
}

void OperationExplanation::Update()
{
}

void OperationExplanation::Draw()
{
}

void OperationExplanation::DrawImgui()
{
	if (!MyImgui::flags[_nodeText])return;

	ImGui::Begin(_nodeText.c_str());

		
	ImGui::Text(_explanationText.c_str());


	ImGui::End();
}
