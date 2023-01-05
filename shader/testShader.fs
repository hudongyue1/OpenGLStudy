#version 330 core

in vec3 ourColor;
out vec4 FragColor;

uniform float timeValue;

void main() {
    FragColor = vec4(timeValue, timeValue, timeValue, 1.0f);
}