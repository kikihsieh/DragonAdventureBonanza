#version 330

layout(location = 0) in vec4 in_position;
uniform mat4 transform;
uniform mat3 projection;

out vec2 vpos;

void main()
{
    vpos = in_position.xy;
    gl_Position = vec4(in_position.xy, 1.0, 1.0);

//    gl_Position = in_position;
    // Convert to the [0, 1] range of UV coordinate
//    uv = (in_position.xy + vec2(1.05, 1.05)) / 2.1;
}
