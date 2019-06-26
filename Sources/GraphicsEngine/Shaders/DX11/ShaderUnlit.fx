//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	float4x4	matrixWorldViewProjT;
	float4		materialColor;
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position	: POSITION;
	float4 Normal	: NORMAL;
	float4 Color	: COLOR;
};

struct PS_INPUT
{
	float4 Position	: SV_POSITION;
	float4 Color	: COLOR;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;

	output.Position	= mul( input.Position, matrixWorldViewProjT );
	output.Color	= materialColor;
    
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
	return input.Color;
}
