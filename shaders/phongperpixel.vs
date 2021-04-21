#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;

uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat3 uNMV;

out vec3 ePos;
out vec3 eNormal;

void main() {
    gl_Position = uMVP * vec4(vPos, 1.0);

    ePos = (uMV * vec4(vPos, 1.0)).xyz;
    eNormal = normalize(uNMV * vNor);
}
