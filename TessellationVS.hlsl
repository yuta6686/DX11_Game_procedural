#include "shaderNoise.hlsl"

// 定数バッファ
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
    float4 Parameter;
    float4 Parameter2;
}

struct VS_OUT
{
    float3 pos : POSITION;
    float2 texel : TEXCOORD0;    
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
void main(in float4 inPosition : POSITION0,
			in float4 inNormal : NORMAL0,
			in float4 inDiffuse : COLOR0,
			in float2 inTexCoord : TEXCOORD0,
            in uint InstanceId : SV_InstanceID,
			
			out VS_OUT Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);    

    Out.pos = mul(inPosition, wvp);
    Out.pos = mul(inPosition, World);    
    
    // outNormal = inNormal;

    // outDiffuse = inDiffuse;

    Out.texel = inTexCoord;
}