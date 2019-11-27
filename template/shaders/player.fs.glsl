#version 330

// From vertex shader
in vec2 texcoord;

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;
uniform float invicibility;

// Output color
layout(location = 0) out  vec4 color;

void main()
{
    if (invicibility == 0.0) {
        color = vec4(fcolor, 1.0) * texture(sampler0, vec2(texcoord.x, texcoord.y));
    }
    else {
        if (sin(5*invicibility/1000.f*2*3.141592653589) >= 0) {
            color = vec4(0.7, 0.0, 0.0, 0.0) + (vec4(fcolor, 1.0) * texture(sampler0, vec2(texcoord.x, texcoord.y)));
        }
        else {
            color = vec4(fcolor, 1.0) * texture(sampler0, vec2(texcoord.x, texcoord.y));
        }
    }
}
