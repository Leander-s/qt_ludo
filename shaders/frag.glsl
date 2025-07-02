#version 330 core

uniform sampler2D tex;

in vec3 vColor;
in vec2 vUV;

out vec4 fragColor;

void main(){
    vec4 texColor = texture(tex, vUV);
    fragColor = texColor;
}
