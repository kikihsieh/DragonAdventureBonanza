#version 330 

// Input attributes
in vec3 in_position;
in vec2 in_texcoord;

// Passed to fragment shader
out vec2 texcoord;

// Application data
uniform mat4 transform;
uniform mat3 projection;

void main()
{
	texcoord = in_texcoord;
	vec4 world_position = transform * vec4(in_position, 1.0);
	vec3 screen_position = projection * vec3(world_position.xy, 1.0);
	gl_Position = vec4(screen_position.xy, world_position.z, 1.0);
}