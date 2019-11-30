#version 330

// From vertex shader
in vec2 texcoord;

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;

// Output color
layout(location = 0) out  vec4 color;

void main()
{
	vec4 temp_color = texture(sampler0, vec2(texcoord.x, texcoord.y));
	if(temp_color.a < 0.5)
		discard;
	color = temp_color;
//	color = vec4(fcolor, 1.0) * texture(sampler0, vec2(texcoord.x, texcoord.y));
}
