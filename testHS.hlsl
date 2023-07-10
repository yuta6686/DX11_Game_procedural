#include "TessellationVS.hlsl"

// �萔�o�b�t�@�P
cbuffer cbBuffer1 : register(b1)
{
    float g_TessFactor : packoffset(c0.x); // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
    float g_InsideTessFactor : packoffset(c0.y); // �p�b�`�����̃e�b�Z���[�V�����W��    
};

// �n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y�p�̏o�̓p�����[�^
struct CONSTANT_HS_OUT
{
    // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
    float Edges[4] : SV_TessFactor; 
    
    // �p�b�`�����̃e�b�Z���[�V�����W��
    float Inside[2] : SV_InsideTessFactor;        
};

// �n���V�F�[�_�[�̃R���g���[���|�C���g �t�F�[�Y�p�̏o�̓p�����[�^
struct HS_OUT
{
    float3 pos : POSITION;
    float2 texel : TEXCOORD0;
};

// *****************************************************************************************
// �n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y
// *****************************************************************************************
CONSTANT_HS_OUT ConstantsHS_Main(InputPatch<VS_OUT,4> ip,uint PatchID : SV_PrimitiveID)
{
    CONSTANT_HS_OUT Out;
    
    Out.Edges[0] = Out.Edges[1] = Out.Edges[2] = Out.Edges[3] = g_TessFactor; // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
    Out.Inside[0] = g_InsideTessFactor; // �p�b�`�����̉����@�̃e�b�Z���[�V�����W��
    Out.Inside[1] = g_InsideTessFactor; // �p�b�`�����̏c���@�̃e�b�Z���[�V�����W��
    
    return Out;
}

// *****************************************************************************************
// �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y
// *****************************************************************************************
[domain("quad")] // �e�b�Z���[�g���郁�b�V���̌`����w�肷��
[partitioning("integer")] // �p�b�`�̕����Ɏg�p����A���S���Y�����w�肷��
[outputtopology("triangle_ccw")] // ���b�V���̏o�͕��@���w�肷��
[outputcontrolpoints(4)] // �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y���R�[��������
[patchconstantfunc("ConstantsHS_Main")] // �Ή�����n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y�̃��C���֐�
HS_OUT HS_Main(InputPatch<VS_OUT, 4> In, uint i : SV_OutputControlPointID, uint PatchID : SV_PrimitiveID)
{
    HS_OUT Out;

  // ���̂܂ܓn��
    Out.pos = In[i].pos;
    Out.texel = In[i].texel;
    return Out;
}