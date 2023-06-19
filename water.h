#pragma once


class CWater : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;


	CShader*		m_Shader;

	float			m_Time;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};