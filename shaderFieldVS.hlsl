// shaderField.hlsl
#include "shaderNoise.hlsl"

// 定数バッファ
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
    float4 Parameter;
    float4 HeightYZW;
    
}


//=============================================================================
// 頂点シェーダ
//=============================================================================
void main(in float4 inPosition : POSITION0,
			in float4 inNormal : NORMAL0,
			in float4 inDiffuse : COLOR0,
			in float2 inTexCoord : TEXCOORD0,
			
			out float4 outPosition : SV_POSITION,
            out float4 outWorldPosition : POSITION0,
			out float4 outNormal : NORMAL0,
			out float4 outDiffuse : COLOR0,
			out float2 outTexCoord : TEXCOORD0)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    inPosition.y = fbm2(inTexCoord * 0.05f, 6,HeightYZW.yz) * HeightYZW.x;
    // ←ここの数値をノイズなどで変えてみる

    outPosition = mul(inPosition, wvp);
    outWorldPosition = mul(inPosition, World);
    
    outNormal = inNormal;

    outDiffuse = inDiffuse;

    outTexCoord = inTexCoord;
}