#pragma once


class CWater : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	static const int FIELD_X = 256;
	static const int FIELD_Z = 256;

	VERTEX_3D m_Vertex[FIELD_X * FIELD_Z];

	CShader*		m_Shader;
	
	inline static XMFLOAT4		m_Parameter;
	inline static XMFLOAT4		m_Parameter2;
	CTexture*		m_Texture;

	bool _isSingle = true;
	
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawImgui();

	void SetIsUseImguiFalse() { _isSingle = false; }
};