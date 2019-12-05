#version 330 

layout(location = 0) in vec4 in_position;

out vec2 uv;
uniform mat3 projection;
uniform float level;

void main()
{
    vec3 offset = projection * vec3(600.f, 400.f, 1.f);
    gl_Position = vec4(in_position.xy, 0.0, 1.0);
    // Convert to the [0, 1] range of UV coordinate
    uv = ((in_position.xy + vec2(1.0, 1.0)) / 2) - vec2(offset.x, 0.0)/(2*level);
}
