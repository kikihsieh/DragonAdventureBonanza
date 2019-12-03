#version 330

uniform sampler2D screen_texture;
uniform float isCave;

in vec2 uv;

layout(location = 0) out vec4 color;

void main()
{
    float x = mod(uv.x, 1.f);
    float y = mod(uv.y, 1.f);
    color = texture(screen_texture, vec2(x,y));
}
