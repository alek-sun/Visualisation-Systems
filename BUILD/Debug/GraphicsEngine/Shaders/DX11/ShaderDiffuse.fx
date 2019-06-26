//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	float4x4	matrixWorldViewProjT;
}

struct Light
{
	float4	type;		// тип источника
	float4	position;	// позиция источника (есть у Point и Spot)
	float4	direction;	// направление света
	float4	color;		// (цвет.r, цвет.g, цвет.b, интенсивность)
};

cbuffer ConstantBuffer : register( b1 )
{
	float4x4	matWorldNormal;
	float4x4	matWorldT;
	float4		materialColor;
	float4		lightsCount;
	Light		lights[3];
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 	LocalPosition	: POSITION;
	float4 	Color			: COLOR;
	float4 	LocalNormal		: NORMAL;
};

struct PS_INPUT
{
	float4	Position		: SV_POSITION;
	float4	Color			: COLOR;
	float4	LocalPosition	: TEXCOORD1;
	float4	LocalNormal		: TEXCOORD2;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;

	output.Position			= mul(input.LocalPosition, matrixWorldViewProjT);
	output.Color			= input.Color;
	output.LocalPosition	= input.LocalPosition;
	output.LocalNormal		= input.LocalNormal;
	    
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float3 calcDiffuse(float4 lightCol, float3 lightDir, float3 vertexNormal)
{
	float diffuse = saturate( dot(-lightDir, vertexNormal) );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	float3 color = diffuse * lightCol.rgb * lightCol.a;

	return color;
}

float4 PS( PS_INPUT input) : SV_Target
{
	float4 outputColor;
	
	float3 col = float3(0,0,0);

	// Переводим нормаль из локальной в глобальную систему координат
	float3 vertexNormal = mul(input.LocalNormal.xyz, matWorldNormal);
	vertexNormal = normalize(vertexNormal);
	
	// Переводим позицию из локальной в глобальную систему координат
	float3 vertexPos = mul(input.LocalPosition, matWorldT);
	
	for (int i = 0; i < 3; ++i)
	{
		// Выходим, как только закончились источники освещения
		if (i >= lightsCount.x) break;
	
		float type = lights[i].type.x;
		float epsilon = 0.001;
		
		float4 lightCol = lights[i].color;
		float3 lightDir = float3(0,0,0);
		
		// Directional light
		if (abs(type - 1) < epsilon)
		{
			lightDir = normalize(lights[i].direction.xyz).xyz;
		}
		// Point light
		else if (abs(type - 2) < epsilon)
		{
			lightDir = normalize(vertexPos - lights[i].position.xyz).xyz;
		}
		
		col += materialColor.rgb * calcDiffuse(lightCol, lightDir, vertexNormal);
	}
	
	outputColor = float4(col, 1.0);
	
	return outputColor;
}
