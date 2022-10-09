#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;

    float rotation;
};
layout(binding = 1) uniform sampler2D source;
void main() {
    vec2 uv = qt_TexCoord0 - vec2(0.5, 0.5);
    float dotValue = dot(uv, uv) * 2.0;

    vec2 coords = qt_TexCoord0;
    // Rotate part of the button
    if (dotValue > 0.2 && dotValue < 0.275) {
        coords -= vec2(0.5);
        float c = cos(rotation);
        float s = sin(rotation);
        coords *= mat2(c, s, -s, c);
        coords += vec2(0.5);
    }
    fragColor = texture(source, coords) * qt_Opacity;
}
