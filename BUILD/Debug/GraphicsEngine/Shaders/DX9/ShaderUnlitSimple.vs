float4x4	matrixWorldViewProjT;
float4		materialColor;

struct VS_INPUT
{
	float4 	Position	: POSITION;
	float4 	Normal		: NORMAL;
	float4 	Color		: COLOR;
};

struct VS_OUTPUT
{
	float4 	Position	: POSITION;
	float4 	Color		: COLOR0;
};

VS_OUTPUT main( VS_INPUT input )
{
	VS_OUTPUT output;

	output.Position	= mul(input.Position, matrixWorldViewProjT);
	//output.Color	= materialColor;
	output.Color	= input.Color;
	
	return output;
};