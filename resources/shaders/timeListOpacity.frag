#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
};
layout(binding = 1) uniform sampler2D source;
void main() {
    const float y = qt_TexCoord0.y;
    float opacity = 1.0;
    float topRangeY = 0.4;
    float bottomRangeY = 0.6;
    if (y < topRangeY) {
        opacity = y / topRangeY;
    } else if (y > bottomRangeY) {
        float percent = (1.0 - y) / (1.0 - bottomRangeY);
        opacity = percent;
    }
    fragColor = texture(source, qt_TexCoord0) * qt_Opacity * opacity;
}
