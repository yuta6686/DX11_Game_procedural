#pragma once

#include <list>
#include <string>
#include "main.h"

#include "game_object.h"

#include "camera.h"
#include "field.h"
#include "model.h"
#include "polygon.h"
#include "sky.h"
#include "water.h"

#include "myImgui.h"

class CScene
{
protected:
	std::list<CGameObject*>	m_GameObject;

public:
	CScene(){}
	virtual ~CScene(){}


	virtual void Init()
	{
		AddGameObject<CCamera>();
		AddGameObject<CField>();
		AddGameObject<CSky>();
		AddGameObject<CWater>();
		//AddGameObject<CModel>();
		//AddGameObject<CModelNormal>();
		//AddGameObject<CPolygon>();
	}

	virtual void Uninit()
	{
		for (CGameObject* object : m_GameObject)
		{
			object->Uninit();
			delete object;
		}

		m_GameObject.clear();
	}


	virtual void Update()
	{
		for( CGameObject* object : m_GameObject )
			object->Update();
	}


	virtual void Draw()
	{
		for (CGameObject* object : m_GameObject)
			object->Draw();
	}

	virtual void DrawImgui()
	{
		for (CGameObject* object : m_GameObject)
			object->DrawImgui();
	}

	void DrawShadow()
	{
		for (CGameObject* object : m_GameObject)
			object->DrawShadow();
	}


	template <typename T>
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject.push_back( gameObject );

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

};