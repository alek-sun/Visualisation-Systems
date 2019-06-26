#version 110

varying vec2 uv1;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
	vec2 uv1Scale = vec2(0.5, 10);
	vec2 uv2Scale = vec2(6, 20);
	vec2 uv3Scale = vec2(2, 10);
	vec3 c = vec3(1.5,1.5,1.5);
	
	vec3 color1 = texture2D( texture1, uv1.xy * uv1Scale ).rgb;
	vec3 color2 = texture2D( texture2, uv1.xy * uv2Scale ).rgb;
	vec3 color3 = texture2D( texture3, uv1.xy * uv3Scale ).rgb;

	gl_FragColor.rgb = color1*color2*color3*c;
	gl_FragColor.a = 1.0;
}