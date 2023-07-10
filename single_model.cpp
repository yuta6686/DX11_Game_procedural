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
	// �}�g���N�X�ݒ�
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


	// ���_�o�b�t�@�ݒ�
	CRenderer::SetVertexBuffers(m_VertexBuffer);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::SetIndexBuffer(m_IndexBuffer);

	// �ʏ�`��
	for (unsigned short i = 0; i < m_SubsetNum; i++)
	{
		// �}�e���A���ݒ�		
		m_Shader->SetMaterial(m_SubsetArray[i].Material.Material);

		// �e�N�X�`���ݒ�
		CRenderer::SetTexture(m_SubsetArray[i].Material.Texture);

		// �|���S���`��
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
