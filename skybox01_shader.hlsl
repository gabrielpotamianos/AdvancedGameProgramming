
Texture2D texture0;
SamplerState sampler0;
cbuffer Cbuffer0
{
	matrix WVP;							//64 bytes
	//total 112 bytes
};


struct VOut
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;
	//float2 texcoord	: TEXCOORD;
	//float2 normal	: NORMAL;
};


VOut VShader(float3 position : POSITION, float4 color : COLOR/*, float2 texcoord : TEXCOORD*/)
{
	VOut output;
	output.color = color;

	float4 default_color = { 0.0f,0.0f,1.0f,1.0f };
	output.position= mul(WVP,float4(position,1.0f));
	//output.texcoord = texcoord;
	//if(color.z!=0)
	//	output.color = default_color;
	//if(color.w!=0)
	//	output.color = default_color;

	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR/*, float2 texcoord : TEXCOORD*/) : SV_TARGET
{
	return color;//*texture0.Sample(sampler0,texcoord);
}
