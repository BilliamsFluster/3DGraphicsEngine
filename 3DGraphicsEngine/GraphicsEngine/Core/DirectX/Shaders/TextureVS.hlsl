cbuffer CBuf
{
    matrix transform;
};

struct VSOut
{
    float2 tex : TEXCOORD;
    float4 pos : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float2 tex : TexCoord)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.0f), transform);
    vso.tex = tex;
    return vso;
}