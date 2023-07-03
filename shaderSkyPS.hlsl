

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
    

    
    //float2 offset = float2(Parameter.x, -Parameter.x) / 10;
    //float2 warp = fbm2(inTexCoord * 1.2 + Parameter.x / 10, 20, offset);
    //inTexCoord += warp;
    
    //outDiffuse.a = fbm2(inTexCoord, 20) + 0.2;                
    
    
    outDiffuse.rgb = 0.0f;
    
    //float3 lightDir = float3(cos(Parameter.w), sin(Parameter.w), 0.0);
    float3 lightDir = Parameter.xyz;
    lightDir = normalize(lightDir);
    
    float3 eyeVector = normalize(inWorldPosition.xyz - CameraPosition.xyz);
    
    float dle = -dot(lightDir, eyeVector);
    
    float3 sunLight = float3(1.0, 1.0, 1.0) * 10;
    float3 wavelength = float3(0.65, 0.57, 0.475);
    float3 wavelength4inv = 1.0 / pow(wavelength, 4);
    
    float atomDensityEye = 0.05 + pow(1.0 - eyeVector.y, 20) * 0.95;
    float atomDensityLight = 0.05 + pow(1.0 + lightDir.y, 20) * 0.95;
    float3 scatteringLight = sunLight *
                exp(-atomDensityLight * atomDensityEye * wavelength4inv * 1.0);
    
    float rayleighPhase = 0.5 + dle * dle;
    outDiffuse.rgb += scatteringLight * atomDensityEye * wavelength4inv * rayleighPhase * 0.1;
    
    // ミー散乱
    float g = 0.990;
    float g2 = g * g;
    float miePhase = 1.5 * ((1.0 - g2) / (2.0 + g2) * (1.0 + dle * dle)
                        / pow((1.0 + g2 - 2.0 * g * dle), 0.5));
    
    outDiffuse.rgb += scatteringLight * miePhase;
    
    // 雲 
    float2 offset = float2(Parameter.w, -Parameter.w) / 10;
    float2 cloudPosition = inWorldPosition.xz / inWorldPosition.y;
    float noise = fbm2(cloudPosition, 5);
    outDiffuse.rgb = lerp(outDiffuse.rgb, float3(1.0, 1.0, 1.0), noise);
    
    // 地平線
    outDiffuse.rgb *= smoothstep(-1.0, 15.0, inWorldPosition.y);
    
    // ラインハルト　トーンマッピング
    outDiffuse.rgb = outDiffuse.rgb / (outDiffuse.rgb + 1.0);
    outDiffuse.a = 1.0;    
}
