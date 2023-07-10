#include "TessellationVS.hlsl"

// 定数バッファ１
cbuffer cbBuffer1 : register(b1)
{
    float g_TessFactor : packoffset(c0.x); // パッチのエッジのテッセレーション係数
    float g_InsideTessFactor : packoffset(c0.y); // パッチ内部のテッセレーション係数    
};

// ハルシェーダーのパッチ定数フェーズ用の出力パラメータ
struct CONSTANT_HS_OUT
{
    // パッチのエッジのテッセレーション係数
    float Edges[4] : SV_TessFactor; 
    
    // パッチ内部のテッセレーション係数
    float Inside[2] : SV_InsideTessFactor;        
};

// ハルシェーダーのコントロールポイント フェーズ用の出力パラメータ
struct HS_OUT
{
    float3 pos : POSITION;
    float2 texel : TEXCOORD0;
};

// *****************************************************************************************
// ハルシェーダーのパッチ定数フェーズ
// *****************************************************************************************
CONSTANT_HS_OUT ConstantsHS_Main(InputPatch<VS_OUT,4> ip,uint PatchID : SV_PrimitiveID)
{
    CONSTANT_HS_OUT Out;
    
    Out.Edges[0] = Out.Edges[1] = Out.Edges[2] = Out.Edges[3] = g_TessFactor; // パッチのエッジのテッセレーション係数
    Out.Inside[0] = g_InsideTessFactor; // パッチ内部の横方法のテッセレーション係数
    Out.Inside[1] = g_InsideTessFactor; // パッチ内部の縦方法のテッセレーション係数
    
    return Out;
}

// *****************************************************************************************
// ハルシェーダーのコントロール ポイント フェーズ
// *****************************************************************************************
[domain("quad")] // テッセレートするメッシュの形状を指定する
[partitioning("integer")] // パッチの分割に使用するアルゴリズムを指定する
[outputtopology("triangle_ccw")] // メッシュの出力方法を指定する
[outputcontrolpoints(4)] // ハルシェーダーのコントロール ポイント フェーズがコールされる回数
[patchconstantfunc("ConstantsHS_Main")] // 対応するハルシェーダーのパッチ定数フェーズのメイン関数
HS_OUT HS_Main(InputPatch<VS_OUT, 4> In, uint i : SV_OutputControlPointID, uint PatchID : SV_PrimitiveID)
{
    HS_OUT Out;

  // そのまま渡す
    Out.pos = In[i].pos;
    Out.texel = In[i].texel;
    return Out;
}