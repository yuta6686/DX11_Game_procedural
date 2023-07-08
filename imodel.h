#pragma once
#include "game_object.h"
#include "model.h"
class IModel :
    public CGameObject
{
protected:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	DX11_SUBSET* m_SubsetArray = NULL;
	unsigned short	m_SubsetNum;

	void LoadObj(const char* FileName, MODEL* Model);
	void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned short* MaterialNum);

	CShader* m_Shader;
	///CTexture*		m_TextureFur;
	
	MyImguiData		_mydata;
public:
	virtual void Init()=0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw()=0;
	void DrawShadow() {};

	void Load(const char* FileName);
	void Unload();
	virtual void DrawImgui()=0;
};

