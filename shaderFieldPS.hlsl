// shaderFieldPS.hlsl

#include "shaderNoise.hlsl"

Texture2D g_Texture : register(t1);
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
    float4 LightParameter;
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
    // グラデーションのテクスチャから色取得
    float noise = fbm2(inTexCoord * 0.05f, Parameter.x, HeightYZW.yz);
    float4 noiseTexture = g_Texture.Sample(g_SamplerState, float2(noise + Parameter.y, 0));
    outDiffuse = noiseTexture;
    
    // 法線マッピング
    float yx1 = fbm2(inTexCoord * 0.05 + float2(0.0001, 0.0), Parameter.x,HeightYZW.yz) * HeightYZW.x;
    float yx2 = fbm2(inTexCoord * 0.05 - float2(0.0001, 0.0), Parameter.x,HeightYZW.yz) * HeightYZW.x;
    float yz1 = fbm2(inTexCoord * 0.05 + float2(0.0, 0.0001), Parameter.x,HeightYZW.yz) * HeightYZW.x;
    float yz2 = fbm2(inTexCoord * 0.05 - float2(0.0, 0.0001), Parameter.x,HeightYZW.yz) * HeightYZW.x;
    float3 vx = float3(0.01, yx2 - yx1, 0.0);
    float3 vz = float3(0.0, yz2 - yz1, 0.01);
    
    float3 normal = normalize(cross(vz, vx));
    
    
    // ライティング
    float3 lightDir = normalize(LightParameter.xyz);
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
    fresnel = 0.05 + (Parameter.w - 0.05) * pow(fresnel, 2.0f);
           
    // 大気散乱    
    float dle = -dot(lightDir, eye);
    float3 sunLight = float3(1.0, 1.0, 1.0) * 5;
    float3 wavelength = float3(0.65, 0.57, 0.475);
    float3 wavelength4inv = 1.0 / pow(wavelength, 4);
    
    float atomDensityEye = 0.05 + pow(1.0 - eye.y, 20) * 0.95;
    float atomDensityLight = 0.05 + pow(1.0 + lightDir.y, 20) * 0.95;
    float3 scatteringLight = sunLight *
                exp(-atomDensityLight * atomDensityEye * wavelength4inv * 1.0);
    
    float rayleighPhase = 0.5 + dle * dle;
    outDiffuse.rgb += scatteringLight * atomDensityEye * wavelength4inv * rayleighPhase * 0.05;
    
    // 距離
    float dist = distance(inWorldPosition.xyz, CameraPosition.xyz);
    
    // 水中入ったら青黒くする
    float waterfog = CameraPosition.y + 3.0 + HeightYZW.x / HeightYZW.x;
    waterfog = 1.0f - saturate(waterfog);
    
    // フォグ    
    float fog = (1.0 - exp(-dist * 0.02 * HeightYZW.w));
    float height = -inWorldPosition.y - 1.0f;
    float fogHeight = saturate(height * 0.2f);
    
    
    // 最終出力    
    outDiffuse *= noiseTexture;
    outDiffuse.rgb = lerp(outDiffuse.rgb, 0.5, fresnel) * light + spec;    
    outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.7,0.7,0.9), fog);
    outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.0, 0.1, 0.5) * light, waterfog);
    
    // ↓入れるよりきれいなので消す
    //outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.1, 0.2, 0.1), fogHeight);    
    
    outDiffuse.a = 1.0f;
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
