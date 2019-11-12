#version 330 

// Input attributes
in vec3 in_position;
in vec2 in_texcoord;

// Passed to fragment shader
out vec2 texcoord;

// Application data
uniform mat3 transform;
uniform mat3 projection;
uniform vec2 offset;
uniform vec2 frames;

void main()
{
//	float row_offset = 0/2.0;
//	float col_offset = 1/6.0;
	texcoord = vec2(in_texcoord.x/frames.x + offset.x,in_texcoord.y/frames.y + offset.y);
	vec3 pos = projection * transform * vec3(in_position.xy, 1.0);
	gl_Position = vec4(pos.xy, in_position.z, 1.0);
}