#version 110

struct Light
{
	vec4	type;		// тип источника
	vec4	position;	// позиция источника (есть у Point и Spot)
	vec4	direction;	// направление света
	vec4	color;		// (цвет.r, цвет.g, цвет.b, интенсивность)
};

// Shader parameters
uniform mat4 matWorldNormal;
uniform mat4 matWorldT;
uniform vec4 materialColor;
uniform vec4 lightsCount;
uniform Light lights[3];
uniform vec4 camPos;
//campos

varying vec3 localPosition;
varying vec3 localNormal;


vec3 calcSpecular(vec4 lightCol, vec3 vertexPos, vec3 vertexNormal)
{
    vec3 h = normalize(normalize(camPos.xyz-vertexPos));
	float specular = clamp( dot(h, vertexNormal), 0.0, 1.0 );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	vec3 color = specular * lightCol.rgb * lightCol.a;

	return color;
}

vec3 calcDiffuse(vec4 lightCol, vec3 lightDir, vec3 vertexNormal)
{
	float diffuse = clamp( dot(-lightDir, vertexNormal), 0.0, 1.0 );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	vec3 color = diffuse * lightCol.rgb * lightCol.a;

	return color;
}

void main()
{
	vec3 col = vec3(0,0,0);

	// Переводим нормаль из локальной в глобальную систему координат
	vec3 vertexNormal = (vec4(localNormal, 0.0) * matWorldNormal).xyz;
	vertexNormal = normalize(vertexNormal);
	
	// Переводим позицию из локальной в глобальную систему координат
	vec3 vertexPos = (vec4(localPosition, 1.0) * matWorldT).xyz;
	
	for (int i = 0; i < 3; ++i)
	{
		// Выходим, как только закончились источники освещения
                if (float(i) >= lightsCount.x) break;
		
		float type = lights[i].type.x;
		float epsilon = 0.001;
		
		vec4 lightCol = lights[i].color;
		vec3 lightDir = vec3(0,0,0);
	
		// Directional light
                if (abs(type - 1.0) < epsilon)
		{
			lightDir = normalize(lights[i].direction.xyz).xyz;
		}
		// Point light
                else if (abs(type - 2.0) < epsilon)
		{
			lightDir = normalize(vertexPos - lights[i].position.xyz).xyz;
		}
		
		col += materialColor.rgb * calcDiffuse(lightCol, lightDir, vertexNormal);
        col += materialColor.rgb * calcSpecular(lightCol, vertexPos, vertexNormal);
	}
	
	gl_FragColor = vec4(col, 1.0);
        gl_FragColor.a = 1.0;
}
