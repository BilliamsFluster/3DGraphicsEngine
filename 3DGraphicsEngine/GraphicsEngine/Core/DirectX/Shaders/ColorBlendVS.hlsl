cbuffer CBuf
{
    matrix transform;
};

struct VSOut
{
    float4 color : COLOR;
    float4 pos : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float4 color : COLOR)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.0f), transform);
    vso.color = color;
    return vso;
}