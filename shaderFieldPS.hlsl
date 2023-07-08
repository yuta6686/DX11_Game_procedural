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
    float4 Parameter;
    float4 HeightYZW;
}

float3 gradation(float param);

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
    float yx1 = fbm2(inTexCoord * 0.05 + float2(0.0001, 0.0), 6,HeightYZW.yz) * HeightYZW.x;
    float yx2 = fbm2(inTexCoord * 0.05 - float2(0.0001, 0.0), 6,HeightYZW.yz) * HeightYZW.x;
    float yz1 = fbm2(inTexCoord * 0.05 + float2(0.0, 0.0001), 6,HeightYZW.yz) * HeightYZW.x;
    float yz2 = fbm2(inTexCoord * 0.05 - float2(0.0, 0.0001), 6,HeightYZW.yz) * HeightYZW.x;
    float3 vx = float3(0.01, yx2 - yx1, 0.0);
    float3 vz = float3(0.0, yz2 - yz1, 0.01);
    
    float3 normal = normalize(cross(vz, vx));
    
    
    // ライティング
    float3 lightDir = normalize(float3(1.0, -1.0, 0.7));
    float3 light = 0.5 - dot(normal, lightDir) * 0.5;
    
    // 視線ベクトル
    float3 eye = inWorldPosition.xyz - CameraPosition.xyz;
    eye = normalize(eye);
    
    // 反射ベクトル
    float3 ref = reflect(lightDir, normal);
    
    // スペキュラー
    float spec = -dot(eye, ref);
    spec = saturate(pow(spec, 20));
    
    // フレネル計算
    float fre = pow(dot(eye, normal), 4.0);
    float fresnel = saturate(1.0 + dot(eye, normal));
    fresnel = 0.05 + (1.0 - 0.05) * pow(fresnel, 1);
    
    // 距離
    float dist = distance(inWorldPosition.xyz, CameraPosition.xyz);
    
    
    // フォグ    
    float fog = (1.0 - exp(-dist * 0.02));
    float height = -inWorldPosition.y - 1.0f;
    float fogHeight = saturate(height * 0.2f);
    
    
    // 最終出力
    float3 color = gradation(inWorldPosition.y / 4 + 1.0);
    outDiffuse.rgb = lerp(color, 0.5, fresnel) * light + spec;    
    outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.7,0.7,0.9), fog);
    // outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.1, 0.2, 0.1), fogHeight);
}


float3 gradation(float param)
{
    float3 color = float3(1.0f, 1.0f, 1.0f);
    
    float3 red = float3(0.25f, 0.5f, 0.0f);
    float3 green = float3(0.0f, 0.6f, 0.0f);
    float3 blue = float3(0.0f, 0.0f, 0.4f);
    float3 white = float3(0.5f, 0.5f, 0.5f);
    float3 black = float3(0.0f, 0.0f, 0.0f);          
    
    return lerp(lerp(blue, green, param / 2), lerp(green,red , param / 2), param);
}
