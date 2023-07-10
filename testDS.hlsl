#include "testHS.hlsl"


cbuffer cbBuffer0 : register(b0)
{
  // ��D��
    column_major float4x4 g_matWVP : packoffset(c0); // ���[���h �~ �r���[ �~ �ˉe �s��
};


// �h���C���V�F�[�_�[�̏o�̓p�����[�^
struct DS_OUT
{
    float3 pos : POSITION;
    float2 texel : TEXCOORD0;
};

// *****************************************************************************************
// �h���C���V�F�[�_�[
// *****************************************************************************************
[domain("quad")]
DS_OUT DS_Main(CONSTANT_HS_OUT In, float2 uv : SV_DomainLocation, const OutputPatch<HS_OUT, 4> patch)
{
    DS_OUT Out;
  
  // ���_���W
    float3 p1 = lerp(patch[1].pos, patch[0].pos, uv.x);
    float3 p2 = lerp(patch[3].pos, patch[2].pos, uv.x);
    float3 p3 = lerp(p1, p2, uv.y);

    Out.pos = mul(float4(p3, 1.0f),g_matWVP);

  // �e�N�Z��
    float2 t1 = lerp(patch[1].texel, patch[0].texel, uv.x);
    float2 t2 = lerp(patch[3].texel, patch[2].texel, uv.x);
    float2 t3 = lerp(t1, t2, uv.y);
    Out.texel = t3;

    return Out;
}