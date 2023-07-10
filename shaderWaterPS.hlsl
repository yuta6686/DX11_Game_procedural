

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
    float4 HeightYZW;
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

    
    float2 uv = inTexCoord;    
    uv /= 10;
    
    
   // 法線マッピング
    float yx1 = fbm2(uv * Parameter.w + float2(0.0001, 0.0), 4,Parameter.x) * HeightYZW.x;
    float yx2 = fbm2(uv * Parameter.w - float2(0.0001, 0.0), 4,Parameter.x) * HeightYZW.x;
    float yz1 = fbm2(uv * Parameter.w + float2(0.0, 0.0001), 4,Parameter.x) * HeightYZW.x;
    float yz2 = fbm2(uv * Parameter.w - float2(0.0, 0.0001), 4, Parameter.x) *HeightYZW.x;
    float3 vx = float3(0.01, yx2 - yx1, 0.0);
    float3 vz = float3(0.0, yz2 - yz1, 0.01);
    
    float4 normal = float4(normalize(cross(vz, vx)), 0.0);
    
        
    
    // ライティング
    float3 lightDir = normalize(float3(1.0, -1.0, 0.5));
    float3 light = 0.5 - dot(normal.xyz, lightDir) * 0.5;
    
    // 視線ベクトル
    float4 eye = inWorldPosition - CameraPosition;
    eye = normalize(eye);
    
    // 環境マッピング計算
    float4 refVec = reflect(eye, normal);
    refVec = normalize(refVec);
    refVec = (refVec + 1.0f) / 2.0f;
    
    float4 envTex = g_Texture.SampleBias(g_SamplerState, refVec.xy, 0.0f);
    
    // 反射ベクトル
    float3 ref = reflect(lightDir, normal.xyz);
    

    
    // スペキュラー
    float spec = -dot(eye, ref);
    spec = saturate(pow(spec, 20));
    
    // フレネル
    float fre = pow(dot(eye, normal),4.0);
    float fresnel = saturate(1.0 + dot(eye, normal));
    fresnel = Parameter.w + (1.0 - Parameter.w) * pow(fresnel, 5);
    
    // 距離
    float dist = distance(inWorldPosition.xyz, CameraPosition.xyz);    
    
    // フォグ
    float fog = (1.0 - exp(-dist * 0.02 * HeightYZW.w));    

    // 最終出力
    
    outDiffuse.rgb = lerp(float3(1, 1, 1) * envTex.rgb, float3(0.1, 0.5, 1), light / 1.1) + spec * fresnel;
    outDiffuse.a = max(light.y + Parameter.z - 0.4, spec) * (0.5f - fre);
    
    outDiffuse.rgb = lerp(outDiffuse.rgb, float3(0.7, 0.7, 0.9), fog);
    
}
