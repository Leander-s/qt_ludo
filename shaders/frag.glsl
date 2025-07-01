#version 330 core

in vec3 vColor;
in vec2 vUV;
out vec4 fragColor;

uniform sampler2D tex;

void main(){
    vec4 texColor = texture(tex, vUV);
    fragColor = texColor + vec4(vColor, 1.0f);
}
