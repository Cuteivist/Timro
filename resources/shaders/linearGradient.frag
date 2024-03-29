#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
};
layout(binding = 1) uniform sampler2D source;
layout(binding = 2) uniform sampler2D sourceRect;
void main() {
    fragColor = texture(sourceRect, qt_TexCoord0)
                    * texture(source, qt_TexCoord0).a
                    * qt_Opacity;
}
