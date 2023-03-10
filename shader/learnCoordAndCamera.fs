#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float upAndDown;

void main() {
    FragColor =  mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1 - TexCoord.x, TexCoord.y)), upAndDown);
}