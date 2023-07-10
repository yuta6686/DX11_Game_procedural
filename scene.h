#pragma once

#include "camera.h"
#include "field.h"
#include "model.h"
#include "polygon.h"
#include "sky.h"
#include "water.h"
#include "operation_explanation.h"

enum LAYER {
	LAYER_BEGIN = 0,
	LAYER_3D,
	LAYER_RENDERING_TEXTURE,
	LAYER_IMGUI,
	LAYER_2D,
	LAYER_LAST,
	LAYER_NUM_MAX,
};

class CScene
{
protected:
	std::list<CGameObject*>	m_GameObject[LAYER_NUM_MAX];

public:
	CScene(){}
	virtual ~CScene(){}


	virtual void Init()
	{		
		CreateGameObject();
	}

	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}

			m_GameObject[i].clear();
		}
	}


	virtual void Update()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}
		}
	}


	virtual void Draw()
	{		
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			if (i == LAYER_RENDERING_TEXTURE)continue;
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void DrawUseRenderingTexture()
	{		
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void DrawImgui()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->DrawImgui();
			}
		}
	}

	void DrawShadow()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->DrawShadow();
			}
		}
	}


	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>
	T* GetGameObject() {
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (auto obj : m_GameObject[i]) {

				//	Œ^‚ð’²‚×‚é(RTTI“®“IŒ^î•ñ)
				if (typeid(*obj) == typeid(T)) {
					return (T*)obj;
				}
			}
		}
		return nullptr;
	}

private:
	void CreateGameObject();
	void CreateWater();

};