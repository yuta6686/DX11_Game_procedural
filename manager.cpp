
#include "scene.h"
#include "manager.h"



CScene*	CManager::m_Scene;


void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();

	m_Scene = new CScene();
	m_Scene->Init();

	MyImgui::InitFlags();
}

void CManager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	CInput::Uninit();
	CRenderer::Uninit();

}

void CManager::Update()
{

	CInput::Update();

	m_Scene->Update();

}

void CManager::Draw()
{

	CRenderer::BeginShadow();

	m_Scene->DrawShadow();


	CRenderer::Begin();

	m_Scene->Draw();

#ifdef _DEBUG
	// CRenderer::imguiDraw();

	const std::string window_name = "Imgui";
	
	ImGui::Begin(window_name.c_str(), &MyImgui::flags[window_name],
		ImGuiWindowFlags_MenuBar );

	ImGui::BeginMenuBar();
	{

		if (ImGui::BeginMenu("main"))
		{
			for (auto& mi : MyImgui::flags)
			{
				ImGui::MenuItem(mi.first.c_str(), NULL, &mi.second);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	m_Scene->DrawImgui();

	ImGui::End();
#endif // _DEBUG

	CRenderer::End();

}
