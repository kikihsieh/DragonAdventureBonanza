#version 330

uniform sampler2D screen_texture;
uniform vec2[] lights;
uniform mat3 projection;
uniform uint numLights;

//in vec2 uv;

layout(location = 0) out vec4 color;

void main()
{
//    float x = mod(uv.x, 1.f);
//    float y = mod(uv.y, 1.f);
//    float ambientStrength = 0.1;
//    vec4 in_color = texture(screen_texture, uv);
//    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
    color = vec4(0.0, 0.0, 0.0, 0.1);
}
