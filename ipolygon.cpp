#include "stdafx.h"
#include "ipolygon.h"

void IPolygon::Init()
{
	InitVertexBuffer();

	InitInside();
}

void IPolygon::Uninit()
{
	m_VertexBuffer->Release();

	UninitInside();
}

void IPolygon::Draw()
{	
	
	SetVertexBuffer();

	SetMatrix();
	SetParameter();

	m_Shader->Set();	


	if(_useTesselation)
		SetTesselation();

	// テクスチャ設定
	CRenderer::SetTexture(m_Texture, 0);

	SetPolygonAndDraw();
}

void IPolygon::InitVertexBuffer()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(_polygonScale, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(_uv, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, _polygonScale, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, _uv);

	vertex[3].Position = XMFLOAT3(_polygonScale, _polygonScale, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(_uv, _uv);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


}

void IPolygon::SetVertexBuffer()
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
}

void IPolygon::SetMatrix()
{
	XMFLOAT4X4 identity;
	DirectX::XMStoreFloat4x4(&identity, XMMatrixIdentity());

	m_Shader->SetWorldMatrix(&identity);
	m_Shader->SetViewMatrix(&identity);

	XMFLOAT4X4 projection;
	DirectX::XMStoreFloat4x4(&projection, XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	m_Shader->SetProjectionMatrix(&projection);
}

void IPolygon::SetParameter()
{
	m_Shader->SetParameter(_myData._parameter);
	m_Shader->SetParameter2(_myData._parameter2);
	m_Shader->SetLightParameter(_myData._lightParameter);
}

void IPolygon::SetTesselation()
{
	m_Shader->SetHallShader();
	m_Shader->SetDomainShader();
}

void IPolygon::SetPolygonAndDraw()
{
	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
