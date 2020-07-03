



Texture2D		cube0;
SamplerState	sampler0;


cbuffer CB1
{
	matrix WVPMatrix;	//64 bytes

};

struct VOut
{
	float4 position	:	SV_POSITION;
	float4 color	:	COLOR;
	float3 texcoord	:	TEXCOORD;
};

VOut SkyBoxVS(float4 position : POSITION, float3 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	output.texcoord = position.xyz;

	output.position = mul(WVPMatrix, position);


	return output;
}

float4 SkyBoxPS(float4 position : SV_POSITION, float4 color : COLOR, float3 texcoord : TEXCOORD) : SV_TARGET
{
	return cube0.Sample(sampler0,texcoord);
}