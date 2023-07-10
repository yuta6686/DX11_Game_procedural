#include "stdafx.h"
#include "scene.h"

#include "torii.h"
#include "spheres.h"
#include "Tesselation.h"

void CScene::CreateGameObject()
{
	AddGameObject<CCamera>(LAYER_BEGIN);
	// AddGameObject<CField>(LAYER_3D);
	//AddGameObject<CSky>();
	// AddGameObject<CWater>(LAYER_RENDERING_TEXTURE);
	// CreateWater();

	AddGameObject<CModel>(LAYER_3D);
	//AddGameObject<CModelNormal>();
	//AddGameObject<CPolygon>();
	AddGameObject<OperationExplanation>(LAYER_IMGUI);
	// AddGameObject<Torii>(LAYER_3D);
	// AddGameObject<Spheres>(LAYER_3D);
	AddGameObject<Tesselation>(LAYER_3D);
}

void CScene::CreateWater()
{
	const int count = 5;
	for (int i = -count; i < count; i++)
	{
		for (int j = -count; j < count; j++) {
			auto water2 = AddGameObject<CWater>(LAYER_RENDERING_TEXTURE);
			water2->SetPosition(XMFLOAT3(50 * i, -3, 50 * j));
			water2->SetIsUseImguiFalse();
		}
	}
}

