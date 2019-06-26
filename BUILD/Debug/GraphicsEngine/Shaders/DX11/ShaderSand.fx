Texture2D		texture1	: register(t0);
SamplerState	state1		: register(s0);

cbuffer ConstantBuffer : register( b0 )
{
	float4x4	matrixWorldViewProjT;
	float4		materialColor;
}

struct VS_INPUT
{
	float4	Position	: POSITION;
	float4	Normal		: NORMAL;
	float4	Color		: COLOR;
	float4	uv1			: TEXCOORD0;
};

struct PS_INPUT
{
	float4	Position	: SV_POSITION;
	float4	Color		: COLOR;
	float4	uv1			: TEXCOORD0;
};


PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;

	output.Position	= mul( input.Position, matrixWorldViewProjT );
	output.Color	= input.Color * materialColor;
	output.uv1		= input.uv1;
    
	return output;
}

float4 PS( PS_INPUT input) : SV_Target
{
	float4 outputColor;

	float2 uv1Scale = float2(0.2, 10);
	float3 color1 = texture1.Sample( state1, input.uv1.xy * uv1Scale ).rgb;
	
	outputColor.rgb = color1;
	outputColor.w   = input.Color.w;
	
	return outputColor;
}
