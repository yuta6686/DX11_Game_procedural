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
    float4 Parameter2;
}

//=============================================================================
// 頂点シェーダ
//=============================================================================
void main(in float4 inPosition : POSITION0,
			in float4 inNormal : NORMAL0,
			in float4 inDiffuse : COLOR0,
			in float2 inTexCoord : TEXCOORD0,
            in uint InstanceId : SV_InstanceID,
			
			out float4 outPosition : SV_POSITION,
            out float4 outWorldPosition : POSITION0,
			out float4 outNormal : NORMAL0,
			out float4 outDiffuse : COLOR0,
			out float2 outTexCoord : TEXCOORD0)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    inPosition.x += fbm2(float2(InstanceId, 0) / 1000, 6, Parameter2.yz + InstanceId + Parameter.x / 10) * Parameter2.x * 5;
    inPosition.y += fbm2(float2(InstanceId, 0) / 2000, 6, Parameter2.yz - InstanceId + Parameter.x / 10) * Parameter2.x / 2 + 3;
    inPosition.z += fbm2(float2(InstanceId, 0) / 300, 6, Parameter2.yz * InstanceId +  Parameter.x / 10) * Parameter2.x * 5;
    
    // inPosition.x = fbm2(inTexCoord * 0.05f, 6, Parameter2.yz * InstanceId * 2) * Parameter2.x;
    // inPosition.z = fbm2(inTexCoord * 0.05f, 6, Parameter2.yz * InstanceId * 3) * Parameter2.x;

    // ←ここの数値をノイズなどで変えてみる

    outPosition = mul(inPosition, wvp);
    outWorldPosition = mul(inPosition, World);
    
    outNormal = inNormal;

    outDiffuse = inDiffuse;

    outTexCoord = inTexCoord;
}