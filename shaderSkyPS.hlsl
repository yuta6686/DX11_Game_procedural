

#include "shaderNoise.hlsl"

Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

// 定数バッファ
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
    float4 Parameter;

}



//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main( in  float4 inPosition		: SV_POSITION,
            in float4 inWorldPosition   : POSITION0,
			in  float4 inNormal			: NORMAL0,
			in  float4 inDiffuse		: COLOR0,
			in  float2 inTexCoord		: TEXCOORD0,

			out float4 outDiffuse		: SV_Target )
{


    
    float2 offset = float2(Parameter.x, -Parameter.x) / 10;
    float2 warp = fbm2(inTexCoord * 1.2 + Parameter.x / 10, 20,offset);
    inTexCoord += warp;
    
    outDiffuse.a = fbm2(inTexCoord, 20) + 0.2;
    outDiffuse.rgb = 1.0f;
    
    
}
