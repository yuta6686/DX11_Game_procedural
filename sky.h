#pragma once


class CSky : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	//CTexture*		m_Texture = NULL;

	CShader*		m_Shader;

	float			m_Time;

	XMFLOAT4		m_Parameter;
	std::string m_Name = "Sky";
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawImgui();

};