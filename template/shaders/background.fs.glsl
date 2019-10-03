#version 330

uniform sampler2D screen_texture;
uniform float dead_timer;

in vec2 uv;

layout(location = 0) out vec4 color;

void main()
{
    color = texture(screen_texture, uv);
}