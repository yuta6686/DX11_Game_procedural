#pragma once



#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

// 頂点構造体
struct VERTEX_3D
{
    XMFLOAT3 Position;
    XMFLOAT3 Normal;
    XMFLOAT4 Diffuse;
    XMFLOAT2 TexCoord;
};



struct VERTEX_3D_NORMAL
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT3 Binormal;
	XMFLOAT3 Tangent;
	XMFLOAT4 Diffuse;
	XMFLOAT2 TexCoord;
};




// 色構造体
struct COLOR
{
	COLOR(){}
	COLOR( float _r, float _g, float _b, float _a )
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	float r;
	float g;
	float b;
	float a;
};

// マテリアル構造体
struct MATERIAL
{
	COLOR		Ambient;
	COLOR		Diffuse;
	COLOR		Specular;
	COLOR		Emission;
	float		Shininess;
	float		Dummy[3];//16bit境界用
};




// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture*	Texture;
};


// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

struct LIGHT
{
	XMFLOAT4	Direction;
	COLOR		Diffuse;
	COLOR		Ambient;
};


class CVertexBuffer;
class CIndexBuffer;
class CTexture;


class CRenderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_D3DDevice;
	static ID3D11DeviceContext*    m_ImmediateContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11DepthStencilView* m_LightDepthStencilView;
	static ID3D11ShaderResourceView* m_LightDepthShaderResourceView;

	// レンダリングテクスチャ
	static ID3D11RenderTargetView* m_PPRenderTargetView;
	static ID3D11ShaderResourceView* m_PPShaderResourceView;

	static ID3D11Buffer* m_MaterialBuffer;

/*
	static XMMATRIX				m_WorldMatrix;
	static XMMATRIX				m_ViewMatrix;
	static XMMATRIX				m_ProjectionMatrix;
*/
	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

private:
#ifdef _DEBUG
	// Our state
	inline static bool show_demo_window = true;
	inline static bool show_another_window = false;
	inline static bool show_hello_world = true;
	inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// inlineは使えなかったら、C++のバージョンを上げるか、Renderer.cpp内で宣言し直してください。
	// プロパティ/ 構成プロパティ /　全般　/C++言語標準 ->自分はC++17にしてます。

#endif // _DEBUG
public:
	static void Init();
	static void Uninit();
	static void BeginShadow();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetVertexBuffers( ID3D11Buffer* VertexBuffer, unsigned int stride=sizeof(VERTEX_3D));
	static void SetIndexBuffer( ID3D11Buffer* IndexBuffer );
	static void SetTexture( CTexture* Texture, unsigned int Slot=0 );
	static void SetMaterial(MATERIAL Material);
	static void SetDepthTexture( unsigned int Slot = 0 );
	static void DrawIndexed( unsigned int IndexCount, unsigned int StartIndexLocation, int BaseVertexLocation );

	static ID3D11Device* GetDevice( void ){ return m_D3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_ImmediateContext; }
	static ID3D11ShaderResourceView* GetPPTexture();
	static void BeginPP();

public:
#ifdef _DEBUG
	static void imguiDraw();
#endif // _DEBUG

private:
	// PCに接続されたグラフィックスカードの中で最も大きなビデオメモリを持つカードを見つけ
	static int GetGPUWithMaxMemory(IDXGIFactory* factory);
};
