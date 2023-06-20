#pragma once


class CWater : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;


	CShader*		m_Shader;
	
	XMFLOAT4		m_Parameter;
	CTexture*		m_Texture;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawImgui();

};