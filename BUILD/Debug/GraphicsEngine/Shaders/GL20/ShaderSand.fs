#version 110

varying vec2 uv1;

uniform sampler2D texture1;


void main()
{
	vec2 uv1Scale = vec2(2, 35);
	vec3 color1 = texture2D( texture1, uv1.xy * uv1Scale ).rgb;
	
	gl_FragColor.rgb = color1;
	gl_FragColor.a = 1.0;
}
