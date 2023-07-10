#include "stdafx.h"
#include "torii.h"

void Torii::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	Load("data/MODEL/torii.obj");

	m_Shader = new CShader();
	m_Shader->Init("InstancingVS.cso", "InstancingPS.cso");

	m_Name = "Torii";
	_mydata._parameter2.x = 50;
	_mydata._parameter2.y = 2.3;
}

void Torii::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	Unload();
}

void Torii::Update()
{
	_mydata._parameter.x += 1.0f / 60.0f;
}

void Torii::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//CRenderer::SetWorldMatrix( &world );

	XMFLOAT4X4 worldf;
	DirectX::XMStoreFloat4x4(&worldf, world);

	m_Shader->SetWorldMatrix(&worldf);


	CCamera* camera = CCamera::GetInstance();
	m_Shader->SetViewMatrix(&camera->GetViewMatrix());
	m_Shader->SetProjectionMatrix(&camera->GetProjectionMatrix());
	m_Shader->SetCameraPosition(&camera->GetPosition());

	m_Shader->SetParameter(_mydata._parameter);
	m_Shader->SetParameter2(_mydata._parameter2);

	m_Shader->Set();


	// 頂点バッファ設定
	CRenderer::SetVertexBuffers(m_VertexBuffer);

	// インデックスバッファ設定
	CRenderer::SetIndexBuffer(m_IndexBuffer);

	// 通常描画
	for (unsigned short i = 0; i < m_SubsetNum; i++)
	{
		// マテリアル設定
		// CRenderer::SetMaterial( m_SubsetArray[i].Material.Material );
		m_Shader->SetMaterial(m_SubsetArray[i].Material.Material);

		// テクスチャ設定
		CRenderer::SetTexture(m_SubsetArray[i].Material.Texture);

		// ポリゴン描画
		// CRenderer::DrawIndexed(m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0);
		CRenderer::GetDeviceContext()->DrawIndexedInstanced(m_SubsetArray[i].IndexNum, _count, m_SubsetArray[i].StartIndex, 0.0, 0);

	}
}

void Torii::DrawImgui()
{
	if (!MyImgui::flags[m_Name])return;

	if (ImGui::TreeNode(m_Name.c_str())) {
		MyImgui::ImguiPosition(&m_Position);
		MyImgui::ImguiScale(&m_Scale);
		ImGui::DragFloat("z", &_mydata._parameter2.x, 0.05f, -20, 100);
		ImGui::DragFloat("OffsetX", &_mydata._parameter2.y, 0.05f, -20, 50);
		ImGui::DragFloat("OffsetY", &_mydata._parameter2.z, 0.05f, -20, 50);
		//ImGui::DragFloat("fog",	&_mydata._parameter2.w, 0.001f, 0.0f,0.1f);
		ImGui::DragFloat("fog", &_mydata._parameter2.w, 0.01f, 0.0f, 1.0f);
		ImGui::TreePop();
	}
}
