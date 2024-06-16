#version 330 core

uniform float window_w;
uniform float window_h;

float window_aspect = window_w / window_h;

out vec4 FragColor;

const int MAX_ITER = 100;

void main() {
    vec2 c = ((gl_FragCoord.xy) / vec2(window_w / window_aspect, window_h)) - vec2(0.5 * window_aspect, 0.5);
    c *= 3;
    vec2 z = vec2(0.0);
    int i;
    for(i = 0; i < MAX_ITER; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        if(length(z) > 2.0) break;
    }
    float t = float(i) / float(MAX_ITER);
    FragColor = vec4(t, 0, 0, 1.0);
}