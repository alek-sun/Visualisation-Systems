float4x4	matrixWorldViewProjT	: register(c0);

struct VS_INPUT
{
	float4 	LocalPosition	: POSITION;
	float4 	Color			: COLOR;
	float4 	LocalNormal		: NORMAL;
};

struct VS_OUTPUT
{
	float4 	Position		: POSITION;
	float4 	Color			: COLOR0;
	float4	LocalPosition	: TEXCOORD1;
	float4	LocalNormal		: TEXCOORD2;
};

VS_OUTPUT main( VS_INPUT input )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.Position			= mul(input.LocalPosition, matrixWorldViewProjT);
	output.Color			= input.Color;
	output.LocalPosition	= input.LocalPosition;
	output.LocalNormal		= input.LocalNormal;
	
	return output;
};