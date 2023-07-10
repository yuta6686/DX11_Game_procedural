
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


//=============================================================================
// 頂点シェーダ
//=============================================================================
void main( in  float4 inPosition		: POSITION0,
			in  float4 inNormal			: NORMAL0,
			in  float4 inDiffuse		: COLOR0,
			in  float2 inTexCoord		: TEXCOORD0,
			
			out float4 outPosition		: SV_POSITION,
            out float4 outWorldPosition : POSITION0,
			out float4 outNormal		: NORMAL0,
			out float4 outDiffuse		: COLOR0,
			out float2 outTexCoord		: TEXCOORD0 )
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
    inPosition.y = fbm2(inTexCoord * Parameter.w, 6, Parameter.x) * Parameter.y;

	outPosition = mul(inPosition, wvp);
    outWorldPosition = mul(inPosition, World);

	outDiffuse = inDiffuse;

	outTexCoord = inTexCoord;
}

