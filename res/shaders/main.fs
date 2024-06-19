#version 330 core

uniform ivec2 window_size;
uniform vec2 offset;
uniform float zoom;

out vec4 FragColor;

const int MAX_ITER = 100;
float width = window_size.x;
float height = window_size.y;

float aspect = width / height;

float map(float value, float min1, float max1, float min2, float max2) { return min2 + (value - min1) * (max2 - min2) / (max1 - min1); }

void main() {
    vec2 c = vec2(
        map(gl_FragCoord.x, 0, width, -2, 2) * aspect + offset.x,
        map(gl_FragCoord.y, 0, height, -2, 2) + offset.y
    );
    c *= zoom;
    
    vec2 z = vec2(0.0);
    int i;
    for(i = 0; i < MAX_ITER; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        if(length(z) > 2.0) break;
    }
    float color;
    if (i == MAX_ITER) color = 0.0;
    else color = float(i) / float(MAX_ITER);

    FragColor = vec4(color, color, color, 1.0);
}