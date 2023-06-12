// shaderFieldPS.hlsl

#include "shaderNoise.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


// 定数バッファ
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main(in float4 inPosition : SV_POSITION,
            in float4 inWorldPosition : POSITION0,
			in float4 inNormal : NORMAL0,
			in float4 inDiffuse : COLOR0,
			in float2 inTexCoord : TEXCOORD0,

			out float4 outDiffuse : SV_Target)
{
    
    outDiffuse = g_Texture.Sample(g_SamplerState, inTexCoord);
    
    // 法線マッピング
    float yx1 = fbm2(inTexCoord * 0.05 + float2(0.0001, 0.0), 6) * 20.0;
    float yx2 = fbm2(inTexCoord * 0.05 - float2(0.0001, 0.0), 6) * 20.0;
    float3 vx = float3(0.01, yx2 - yx1, 0.0);
    float yz1 = fbm2(inTexCoord * 0.05 + float2(0.0, 0.0001), 6) * 20.0;
    float yz2 = fbm2(inTexCoord * 0.05 - float2(0.0, 0.0001), 6) * 20.0;
    float3 vz = float3(0.0, yz2 - yz1, 0.01);
    
    float3 normal = normalize(cross(vz, vx));
    
    
		// ライティング
    float3 lightDir = normalize(float3(1.0, -1.0, 1.0));
    float3 light = 0.5 - dot(normal, lightDir) * 0.5;
    
    outDiffuse.rgb *= light;    
    //outDiffuse.rgb = normal;

}