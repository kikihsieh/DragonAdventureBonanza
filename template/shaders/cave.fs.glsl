#version 330

uniform sampler2D screen_texture;
uniform vec2[35] lights;
uniform float[35] flicker;
uniform mat4 transform;
uniform mat3 projection;
uniform int numLights;
uniform vec2 player;

in vec2 vpos;

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.0, 0.0, 0.0, 0.9);
    float lightDist = 1000;
    if (numLights > 0 ) {
        for (int i = 0; i < 35; i++) {
            float radius = distance((projection * vec3(lights[i], 1.0)).xy * vec2(12.0/8.0, 1.0), vec2(vpos.x*(12.0/8.0), vpos.y));
            float dist = distance((projection * vec3(lights[i], 1.0)).xy * vec2(12.0/8.0, 1.0), (projection * vec3(player, 1.0)).xy * vec2(12.0/8.0, 1.0));
            if (dist < lightDist){
                lightDist = dist;
            }
            if (radius < 1.0) {
                color.xyz += (1.0 - radius) * 0.6 * vec3(2.25, 1.25, 0.0);
                color.a -= (1-radius)*(0.4);
                color.a += ((0.08*(sin(flicker[i]*2*3.141592653589) + 1.f)) + (0.10*(sin(flicker[i]/100000.f*2*3.141592653589) + 1.f))) * (1-radius);
                color.a = min(color.a, 0.9);
            }
            if (i == numLights-1)
                break;
        }
    }
    float radius = distance((projection * vec3(player, 1.0)).xy * vec2(12.0/8.0, 1.0), vec2(vpos.x*(12.0/8.0), vpos.y));
    if(radius < 1.0) {
        color.a -= ((1.0-radius)*0.9)*min(lightDist/2, 1.0);
    }
}
