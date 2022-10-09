#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    int shadowCount;
    vec4 shadowColor;
    float currentAngle;
    vec2 ratio;
};
layout(binding = 1) uniform sampler2D source;
void main() {
    float PI = 3.14;
    vec4 bgColor = texture(source, qt_TexCoord0) * qt_Opacity;
    if (bgColor.a < 0.02) {
        fragColor = bgColor;
        return;
    }
    vec2 uv = (qt_TexCoord0 - vec2(0.5, 0.5)) * ratio;
    float uvAtan = atan(uv.x, uv.y) + PI / 2.0 + radians(currentAngle);
    fragColor = mix(bgColor, shadowColor, sin(float(shadowCount) * uvAtan) * bgColor.a);
}
