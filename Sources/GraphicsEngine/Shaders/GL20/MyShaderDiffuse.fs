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


vec3 calcSpecular(vec4 lightCol, vec3 lightDir, vec3 vertexPos, vec3 vertexNormal)
{
    vec3 h = normalize(normalize(camPos.xyz-vertexPos) - lightDir);
	float specular = pow(clamp(dot(h, vertexNormal), 0.0, 1.0 ), 700.0);
	
	vec3 color = specular * lightCol.rgb * lightCol.a;

	return color;
}

vec3 calcDiffuse(vec4 lightCol, vec3 lightDir, vec3 vertexNormal)
{
	float diffuse = clamp(dot(-lightDir, vertexNormal), 0.0, 1.0 );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	vec3 color = diffuse * lightCol.rgb * lightCol.a;

	return color;
}

float calcAttenuation(vec3 vertexPos, vec3 lightDir, vec4 type, vec3 lightPos)
{
    if (type.x == 1.0) return 1.0;
    float d = length(vertexPos - lightPos);
    float att = clamp((1.0/(0.0008*d*d)), 0.0, 1.0);
    return att;
}

float calcSpotFactor(vec4 type, vec3 lightPos, vec3 lightDir, float phi, float theta){
    if (type.x == 1.0 || type.x == 2.0) return 1.0;
    float rho = length(-lightDir)*length(lightPos);
    if (rho < cos(phi/2.0)) return 0.0;
    return pow((rho - cos(phi/2.0)) / (cos(theta/2.0) - cos(phi/2.0)), 0.04);
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
        //Specular light
                else if (abs(type - 3.0) < epsilon)
		{
			lightDir = normalize(vertexPos - lights[i].position.xyz).xyz;
		}
		
		col += (materialColor.rgb * calcDiffuse(lightCol, lightDir, vertexNormal)
            *calcAttenuation(vertexPos, lightDir, lights[i].type, lights[i].position.xyz))
            *calcSpotFactor(lights[i].type, lights[i].position.xyz, lightDir, 6.0, 3.0);
        col += (calcSpecular(lightCol, lightDir, vertexPos, vertexNormal)
            *calcAttenuation(vertexPos, lightDir, lights[i].type, lights[i].position.xyz))
            *calcSpotFactor(lights[i].type, lights[i].position.xyz, lightDir, 6.0, 3.0);;
	}
	
	gl_FragColor = vec4(col, 1.0);
        gl_FragColor.a = 1.0;
}
