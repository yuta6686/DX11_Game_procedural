#pragma once
#include "game_object.h"
class IPolygon :
    public CGameObject
{
	ID3D11Buffer* m_VertexBuffer = NULL;
protected:
	CShader* m_Shader;
	CTexture* m_Texture;

	MyImguiData _myData;
	float _polygonScale = 100.0f;
	float _uv = 1.0f;
	bool _useTesselation = false;
public:
	virtual void Init();
	virtual void InitInside() = 0;
	virtual void Uninit();
	virtual void UninitInside() = 0;
	virtual void Update() = 0;
	virtual void Draw();
	virtual void DrawShadow() = 0;
	virtual void DrawImgui() = 0;

protected:
	void InitVertexBuffer();
	void SetVertexBuffer();
	void SetMatrix();
	void SetParameter();
	void SetTesselation();
	void SetPolygonAndDraw();
};

