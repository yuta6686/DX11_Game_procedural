
#include "main.h"
#include "renderer.h"
#include "shader.h"

#include "game_object.h"
#include "texture.h"
#include "camera.h"
#include "water.h"





void CWater::Init()
{
	//VERTEX_3D vertex[4];

	//vertex[0].Position = XMFLOAT3( -25.0f, 0.0f, 25.0f);
	//vertex[0].Normal   = XMFLOAT3( 0.0f, 1.0f, 0.0f );
	//vertex[0].Diffuse  = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	//vertex[0].TexCoord = XMFLOAT2( 0.0f, 0.0f );

	//vertex[1].Position = XMFLOAT3(25.0f, 0.0f, 25.0f);
	//vertex[1].Normal   = XMFLOAT3( 0.0f, 1.0f, 0.0f );
	//vertex[1].Diffuse  = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	//vertex[1].TexCoord = XMFLOAT2( 100.0f, 0.0f );

	//vertex[2].Position = XMFLOAT3( -25.0f, 0.0f, -25.0f);
	//vertex[2].Normal   = XMFLOAT3( 0.0f, 1.0f, 0.0f );
	//vertex[2].Diffuse  = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	//vertex[2].TexCoord = XMFLOAT2( 0.0f, 100.0f );

	//vertex[3].Position = XMFLOAT3(25.0f, 0.0f, -25.0f);
	//vertex[3].Normal   = XMFLOAT3( 0.0f, 1.0f, 0.0f );
	//vertex[3].Diffuse  = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	//vertex[3].TexCoord = XMFLOAT2( 100.0f, 100.0f );

	for (int z = 0; z < FIELD_Z; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			m_Vertex[z * FIELD_X + x].Position.x = x / 5.0f - FIELD_X / 5.0f / 2;
			m_Vertex[z * FIELD_X + x].Position.z = -z / 5.0f + FIELD_Z / 5.0f / 2;
			m_Vertex[z * FIELD_X + x].Position.y = 0.0f;
			m_Vertex[z * FIELD_X + x].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[z * FIELD_X + x].TexCoord = XMFLOAT2(x / 5.0f, z / 5.0f);
			m_Vertex[z * FIELD_X + x].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
	}


	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * FIELD_X * FIELD_Z;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.pSysMem = m_Vertex;

	CRenderer::GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );

	
	unsigned int index[(FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2];

	unsigned int i = 0;
	for (int z = 0; z < FIELD_Z - 1; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			index[i] = (z + 1) * FIELD_X + x;
			i++;
			index[i] = z * FIELD_X + x;
			i++;
		}

		if (z == FIELD_Z - 2)
			break;

		index[i] = z * FIELD_X + FIELD_X - 1;
		i++;
		index[i] = (z + 2) * FIELD_X;
		i++;
	}

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}



	m_Position = XMFLOAT3( 0.0f, -3.0f, 0.0f );
	m_Rotation = XMFLOAT3( 0.0f, 0.0f, 0.0f );
	m_Scale = XMFLOAT3( 1.0f, 1.0f, 1.0f );



	m_Shader = new CShader();
	m_Shader->Init("shaderWaterVS.cso", "shaderWaterPS.cso");

	m_Texture = new CTexture();
	m_Texture->Load("data/TEXTURE/field004.tga");

	m_Parameter.x = 0.0f;
	m_Parameter.y = 1.5f;
	m_Parameter.z = 2.0f;
	m_Parameter.w = 0.6f;
	
	m_Parameter2.x = 1;

	m_Name = "Water";
	MyImgui::flags[m_Name] = true;
}


void CWater::Uninit()
{

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;

}


void CWater::Update()
{
	if (_isSingle == false)return;
	m_Parameter.x += 1.0f / 60.0f;

}


void CWater::Draw()
{

	// 頂点バッファ設定
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	// インデックスバッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	

	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling( m_Scale.x, m_Scale.y, m_Scale.z );
	world *= XMMatrixRotationRollPitchYaw( m_Rotation.x, m_Rotation.y, m_Rotation.z );
	world *= XMMatrixTranslation( m_Position.x, m_Position.y, m_Position.z );


	XMFLOAT4X4 worldf;
	DirectX::XMStoreFloat4x4(&worldf, world);

	m_Shader->SetWorldMatrix(&worldf);	

	// レンダリングテクスチャを使う
	ID3D11ShaderResourceView* ppTexture = CRenderer::GetPPTexture();
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &ppTexture);	

	CCamera* camera = CCamera::GetInstance();
	m_Shader->SetViewMatrix(&camera->GetViewMatrix());
	m_Shader->SetProjectionMatrix(&camera->GetProjectionMatrix());
	m_Shader->SetCameraPosition(&camera->GetPosition());

	m_Shader->SetParameter(m_Parameter);
	m_Shader->SetParameter2(m_Parameter2);

	m_Shader->Set();



	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ポリゴン描画
//	CRenderer::GetDeviceContext()->Draw( 4, 0 );

	// ポリゴン描画
	CRenderer::GetDeviceContext()->DrawIndexed(((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2), 0, 0);

}

void CWater::DrawImgui()
{
	if (_isSingle == false)return;
	if (MyImgui::flags[m_Name] == false)return;

	if (ImGui::TreeNode(m_Name.c_str())) {

		ImGui::DragFloat("y", &m_Parameter.y, 0.01f, -10, 100);
		ImGui::DragFloat("z", &m_Parameter.z, 0.01f, -10, 10);
		ImGui::DragFloat("w", &m_Parameter.w, 0.01f, 0, 1);

		ImGui::DragFloat("2z",		&m_Parameter2.x, 0.05f, -20, 50);
		ImGui::DragFloat("OffsetX", &m_Parameter2.y, 0.05f, -20, 50);
		ImGui::DragFloat("OffsetY", &m_Parameter2.z, 0.05f, -20, 50);
		//ImGui::DragFloat("fog",	&m_Parameter2.w, 0.001f, 0.0f,0.1f);
		ImGui::DragFloat("fog",		&m_Parameter2.w, 0.01f, 0.0f, 1.0f);
		ImGui::TreePop();
		
	}
}
