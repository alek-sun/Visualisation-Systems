float4x4	matrixWorldViewProjT;
float4		materialColor;

struct VS_INPUT
{
	float4 	Position	: POSITION;
	float4 	Normal		: NORMAL;
	float4 	Color		: COLOR;
	float4	uv1			: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 	Position	: POSITION;
	float4 	Color		: COLOR0;
	float4	uv1			: TEXCOORD0;
};

VS_OUTPUT main( VS_INPUT input )
{
	VS_OUTPUT output;

	output.Position	= mul( input.Position, matrixWorldViewProjT );
	output.Color	= input.Color;
	output.uv1		= input.uv1;
	
	return output;
};