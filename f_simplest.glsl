#version 330 core

in vec2 TexCoord_FS;

out vec4 pixelColor;

uniform sampler2D tex;

void main(void) {
    vec4 textureColor = texture(tex, TexCoord_FS);
    pixelColor = textureColor;

}