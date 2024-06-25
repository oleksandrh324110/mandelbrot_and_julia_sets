#version 330 core

uniform ivec2 window_size;
uniform vec2 offset;
uniform float zoom;

out vec4 FragColor;

const int MAX_ITER = 128;
float width = window_size.x;
float height = window_size.y;

float aspect = width / height;

float map(float value, float min1, float max1, float min2, float max2) { return min2 + (value - min1) * (max2 - min2) / (max1 - min1); }

vec3 hueShift(vec3 color, float hueAdjust){
    const vec3 kRGBToYPrime = vec3 (0.299, 0.587, 0.114);
    const vec3 kRGBToI = vec3 (0.596, -0.275, -0.321);
    const vec3 kRGBToQ = vec3 (0.212, -0.523, 0.311);

    const vec3 kYIQToR = vec3 (1.0, 0.956, 0.621);
    const vec3 kYIQToG = vec3 (1.0, -0.272, -0.647);
    const vec3 kYIQToB = vec3 (1.0, -1.107, 1.704);

    float YPrime = dot(color, kRGBToYPrime);
    float I = dot(color, kRGBToI);
    float Q = dot(color, kRGBToQ);
    float hue = atan(Q, I);
    float chroma  = sqrt(I * I + Q * Q);

    hue += hueAdjust;

    Q = chroma * sin(hue);
    I = chroma * cos(hue);

    vec3 yIQ = vec3(YPrime, I, Q);

    return vec3(dot(yIQ, kYIQToR), dot(yIQ, kYIQToG), dot(yIQ, kYIQToB));
}

void main() {
    vec2 c = vec2(
        map(gl_FragCoord.x, 0, width, -2, 2) * aspect + offset.x / zoom,
        map(gl_FragCoord.y, 0, height, -2, 2) + offset.y / zoom
    );
    c *= zoom;
    
    vec2 z = vec2(0);
    int i;
    for (i = 0; i < MAX_ITER; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        if (length(z) > 16) break;
    }

    vec3 color = vec3(0.2, 0.8, 1);
    if (i == MAX_ITER) color = vec3(0);
    else color = hueShift(color, float(i) / 10);

    FragColor = vec4(color, 1);
}