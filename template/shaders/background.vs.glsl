#version 330 

layout(location = 0) in vec4 in_position;

out vec2 uv;
uniform mat3 projection;
uniform vec2 dims;

void main()
{
    vec3 offset = projection * vec3(600.f, 400.f, 1.f);
    gl_Position = in_position;

    // Convert to the [0, 1] range of UV coordinate
//    uv = ((in_position.xy / vec2(14400.0/1200.0, 1632.0/800) + vec2(1.0, 1.0)) / 2) - (vec2(offset.x, offset.y)/vec2(14400.0/1200.0, 1632.0/800));
    uv = (((in_position.xy + vec2(1.0, 1.0)) / 2) - 0.25*vec2(offset.x, 0.0));
}
