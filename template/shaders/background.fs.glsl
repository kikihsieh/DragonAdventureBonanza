#version 330

uniform sampler2D screen_texture;
uniform float isCave;

in vec2 uv;

layout(location = 0) out vec4 color;

void main()
{
    float x = mod(uv.x, 1.f);
    float y = mod(uv.y, 1.f);
    if (isCave == 1.0) {
        float ambientStrength = 0.5;
        vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
        vec4 samp = texture(screen_texture, vec2(x,y));
        color = samp * vec4(ambient, 1);
    } else {
        color = texture(screen_texture, vec2(x,y));
    }
}
