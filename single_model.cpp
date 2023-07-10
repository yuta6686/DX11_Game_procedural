#include "stdafx.h"
#include "single_model.h"



void SingleModel::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	Unload();
}

void SingleModel::Draw()
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
		m_Shader->SetMaterial(m_SubsetArray[i].Material.Material);

		// テクスチャ設定
		CRenderer::SetTexture(m_SubsetArray[i].Material.Texture);

		// ポリゴン描画
		CRenderer::DrawIndexed(m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0);
		

	}
}

void SingleModel::InitShader(const char* VS, const char* PS)
{
	m_Shader = new CShader();	
	m_Shader->Init(VS, PS);
}

void SingleModel::InitName(std::string name)
{
	m_Name = name;
}

void SingleModel::InitTransform()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}
