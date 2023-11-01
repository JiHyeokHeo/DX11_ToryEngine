
struct VS_INPUT
{
    float4 postion : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 postion : SV_Position;
    float4 color : COLOR;
};
//     ¿©±â
// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.postion = input.postion;
    output.color = input.color;
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    
    return float4(1, 0, 0, 0);
}